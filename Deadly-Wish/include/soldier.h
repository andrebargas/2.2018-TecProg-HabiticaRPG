#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine;

class Soldier : public Character {
public:
    Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);
    
protected:
    void heavy_attack();
    void light_attack();
    void defense();
    void special();
};

#endif