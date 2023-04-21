#pragma once

#include "../sdl_framework_files/sdl_framework.h"
#include "Ball.h"
#include "Platform.h"
#include "Resources.h"
#include "Level.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>


int frameworkrun(Level * f, const int & argc, char* argv[]);


/*
const std::vector<int> sprites_ids = {1,41,42,50,58,65,67,68,509};

class ARKANOID_GAME :public SDL_Framework{
private:
    Window * window;
    unsigned int COLS = 5;
    unsigned int ROWS = 5;
    bool launched = false;
    bool win = false;
    bool lost = false;
    unsigned int destroyed = 0;
    unsigned int BLCKNUM = COLS*ROWS;
    float modx = 1.0;
    float mody = 1.0;
    float timer = 0.0;
    float timer_ability = 0.0;
    float ability_duration = 0.0;
    std::vector<Entity> blocks;
    Entity background;
    Entity loseback;
    Entity winback;
    Entity point;
    Entity ability_up,ability_down;
    Ball ball;
    Platform platform;
    std::unordered_map<std::string, float> conf;
    std::unordered_map<int, Sprite> sprites;
public:
    ARKANOID_GAME();                                        // construct Window
    virtual ~ARKANOID_GAME();                               // destruct Window
    virtual bool LoadConfig();                              // read config from text file, returns false if failed, true otherwise
    virtual bool Init(const int & argc, char* argv[]);      // load and set sprites, returns false if failed, true otherwise
    virtual int Tick();                                    // game tick actions, return value: if true will exit the application

    // param: xrel, yrel: The relative motion in the X/Y direction    param: x, y : coordinate, relative to window
    virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
    virtual void onKeyPressed(FRKey k, bool isReleased);
    virtual void onKeyReleased(FRKey k);
};
*/