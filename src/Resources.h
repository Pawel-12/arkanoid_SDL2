#pragma once

#include "../sdl_framework_files/sdl_framework.h"
#include "Ball.h"
#include "Platform.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>
const std::vector<int> sprites_ids = {1,41,42,50,58,65,67,68,509};

class Resources {
private:
    Window * window;
    Entity background;
    Entity point;
    Entity ability_up,ability_down;
    Ball ball;
    Platform platform;
    std::unordered_map<std::string, float> conf;
    std::unordered_map<int, Sprite> sprites;
    unsigned int COLS = 5;
    unsigned int ROWS = 5;
    unsigned int BLCKNUM = COLS*ROWS;
    std::vector<Entity> blocks;

    friend class Level;

    void startsetup();
    void reset();

public:
    Resources(){
        window = new Window();
    }
    ~Resources() {
        window->Close_SDL();
        delete window;
    }

    bool LoadConfig();                   // read config from text file, returns false if failed, true otherwise
    bool Init(const int & argc, char* argv[]);
    void nextlevel();
};