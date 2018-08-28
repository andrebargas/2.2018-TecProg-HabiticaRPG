#ifndef WINNER_LEVEL_H
#define WINNER_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>

#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

#define MAX_W 16
#define MAX_H 12

class WinnerLevel : public Level {
public:
    WinnerLevel(const string& next = "", int winner_player = -1);
    ~WinnerLevel();

    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void set_congratulations_string();

private:
    bool m_done;
    string m_next;
    string m_congratulations;
    int m_start;
    int m_winner_player;

    shared_ptr<Texture> m_texture;
};

#endif
