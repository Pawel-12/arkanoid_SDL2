//
// Created by Paweł on 30.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_GAME_H
#define ARKANOID_GAME_SDL2_GAME_H

#include "sdl_framework_files/sdl_framework.h"
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


int frameworkrun(Level * f, const int & argc, char* argv[]){

    Resources resources;
    if(!resources.LoadConfig())
        return 0;

    if(!resources.Init( argc, argv))
        return 0;

    SDL_Event e;
    int quit = 0;
    *f = Level(&resources);

    while (quit != 2){
        while (SDL_PollEvent(&e)){

            if (e.type == SDL_QUIT)
                quit = 2;

            if (e.type == SDL_MOUSEMOTION)
                f->onMouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel );

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        f->onMouseButtonClick(FRMouseButton::LEFT, e.button.state);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        f->onMouseButtonClick(FRMouseButton::MIDDLE, e.button.state);
                        break;

                    case SDL_BUTTON_RIGHT:
                        f->onMouseButtonClick(FRMouseButton::RIGHT, e.button.state);
                        break;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                    case SDLK_d:
                        f->onKeyPressed(FRKey::RIGHT, e.key.state);
                        break;

                    case SDLK_LEFT:
                    case SDLK_a:
                        f->onKeyPressed(FRKey::LEFT, e.key.state);
                        break;

                    case SDLK_UP:
                    case SDLK_w:
                        f->onKeyPressed(FRKey::UP, e.key.state);
                        break;

                    case SDLK_DOWN:
                    case SDLK_s:
                        f->onKeyPressed(FRKey::DOWN, e.key.state);
                        break;
                }
            }

            if (e.type == SDL_KEYUP && e.key.type == SDL_KEYUP){
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        f->onKeyReleased(FRKey::RIGHT);
                        break;

                    case SDLK_LEFT:
                        f->onKeyReleased(FRKey::LEFT);
                        break;

                    case SDLK_UP:
                        f->onKeyReleased(FRKey::UP);
                        break;

                    case SDLK_DOWN:
                        f->onKeyReleased(FRKey::DOWN);
                        break;
                }
            }
        }

        if(quit == 2){
            delete f;
            f = nullptr;
            return 11;
        }
        else if(quit == 1)
        {
            delete f;
            resources.nextlevel();
            f = new Level(&resources);
            quit = 0;
        }
        quit = f->Tick();
    }

    delete f;
    f = nullptr;
    return 12;

}



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
#endif //ARKANOID_GAME_SDL2_GAME_H
