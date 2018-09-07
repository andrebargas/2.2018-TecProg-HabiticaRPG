#include "frost_nova.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FROST_NOVA_BASE_DAMAGE 40


using namespace std;
using namespace ijengine;


FrostNova::FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, FROST_NOVA_BASE_DAMAGE, mage_id), m_character_id(mage_id), m_dx(dx/hypot(dx, dy)),
        m_dy(dy/hypot(dx, dy)), m_speed(100.0) 
{
    m_frame = 0;
    m_start = 0;
    m_sprite_path = choose_sprite_path(mage_id);

    m_texture = ijengine::resources::get_texture(m_sprite_path);
    m_x = xp;
    m_y = yp;
    double hip = sqrt(48 * 48 * 2);
    m_x -= hip / 2.0;
    m_y -= hip / 2.0;
    m_bounding_box = Rectangle(m_x, m_y, 96.00, 96.00);
    m_damage = FROST_NOVA_BASE_DAMAGE;
    printf("Frost nova damage: %d\n", m_damage);
}

FrostNova::~FrostNova()
{

}

void
FrostNova::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) 96.0 * m_frame, 0.0, 96.00, 96.00};
    canvas->draw(m_texture.get(),rect, x(), y()); 
}

void
FrostNova::update_self(unsigned now, unsigned last)
{
    update_time(now);
}

bool
FrostNova::active() const
{
    return true;
}

const Rectangle& 
FrostNova::bounding_box() const
{
    return m_bounding_box;
}

const list<Rectangle>&
FrostNova::hit_boxes() const {
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

pair<double, double>
FrostNova::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
FrostNova::update_time(unsigned now)
{
    // if it's the first update self
    if(m_start == 0) {
        m_start = now;
        m_current_time = now;
    }

    if (now - m_current_time > 100)
    {
        m_current_time += 100;
        m_frame = (m_frame + 1) % (m_texture->w() / 96);
    }

    if((m_current_time - m_start) > 100 * 6) {
        invalidate();
    }

}

string
FrostNova::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    switch(player_id) {
        case PLAYER_1:
            directory = "Green";
            break;

        case PLAYER_2:
            directory = "Blue";
            break;

        case PLAYER_3:
            directory = "Yellow";
            break;

        case PLAYER_4:
            directory = "Red";
            break;

        default:
            printf("Valor inválido na FrostNova\n");
            break;
    }

    sprite_path = "Spritesheets/" + directory + "/ObjectFrostNova" + directory + ".png";

    return sprite_path;
}

void
FrostNova::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);

    bool c_bool = c and c->id() != m_character_id;
    bool b_bool = b and b->base_player_id() != m_character_id;

    if(c_bool) {
        m_collided |= (1 << c->id());
    }
    if(b_bool) {
        m_collided |= (1 << ((b->base_player_id() + 4)));
    }

    // if ( (c and c->id() != m_character_id) || (b and b->base_player_id() != m_character_id) )
    // {
    //     printf("OI\n");
    //     invalidate();
    // }
}