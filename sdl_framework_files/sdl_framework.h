//
// Created by Paweł on 27.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_SDL_FRAMEWORK_H
#define ARKANOID_GAME_SDL2_SDL_FRAMEWORK_H

#include <iostream>         // std IO
#include <SDL2/SDL.h>       // SDL2

#include "Window.h"         // Window class for SDL window
#include "Sprite.h"         // Sprite class for SDL textures
#include "Entity.h"         // Entity class for program entities
#include "logSDLerr.h"      // error log function

// class enums for keyboard and mouse input
enum class FRKey {
    RIGHT,
    LEFT,
    DOWN,
    UP
};
enum class FRMouseButton {
    LEFT,
    MIDDLE,
    RIGHT
};

// function to handle console arguments
bool Handle_Console_Args(Window & w, const int & argc, char* argv[] );

// framework class
class SDL_Framework {
private:
    Window * window{};
public:
    SDL_Framework()= default;
    virtual ~SDL_Framework() {};        // virtual desctructor
    virtual bool LoadConfig() = 0;      // read config from text file, returns false if failed, true otherwise
    virtual bool Init() = 0;            // returns false if Init failed, true otherwise
    virtual bool Tick() = 0;            // return value: if true will exit the application

    // param: xrel, yrel: The relative motion in the X/Y direction
    // param: x, y : coordinate, relative to window
    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;
    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;
    virtual void onKeyPressed(FRKey k, bool isReleased) = 0;
    virtual void onKeyReleased(FRKey k) = 0;
};

// function to run framework
int frameworkrun(SDL_Framework * f);

#endif //ARKANOID_GAME_SDL2_SDL_FRAMEWORK_H
