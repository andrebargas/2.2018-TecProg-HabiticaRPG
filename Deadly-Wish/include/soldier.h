#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine;

class Soldier : public Character {
public:
    Soldier(vector<string> sprite_paths, unsigned new_character_id,
     double position_axis_x, double position_axis_y, int character_code);

protected:
    void do_heavy_attack();
    void do_light_attack();
    void do_defense();
    void do_special();
};

#endif
