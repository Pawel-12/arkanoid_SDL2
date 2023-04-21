#pragma once

#include "../sdl_framework_files/sdl_framework.h"
#include "Ball.h"
#include "Platform.h"
#include "Resources.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>


class Level :public SDL_Framework{
private:
    Resources * res;
    bool launched = false;
    unsigned int destroyed = 0;
    float modx = 1.0;
    float mody = 1.0;
    float timer_ability = 0.0;
    float ability_duration = 0.0;
public:
    explicit Level(Resources * r);
    Level() = default;
    virtual ~Level();
    int Tick();                                             // game tick actions, 0 - keep running, 1 - next level, 2 - close

    // param: xrel, yrel: The relative motion in the X/Y direction    param: x, y : coordinate, relative to window
    virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
    virtual void onKeyPressed(FRKey k, bool isReleased);
    virtual void onKeyReleased(FRKey k){};

   // bool LoadConfig(){};
   // bool Init(const int & argc, char* argv[]){};
};