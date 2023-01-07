//
// Created by Paweł on 29.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_WINDOW_H
#define ARKANOID_GAME_SDL2_WINDOW_H
extern float WINDOWWIDTH;
extern float WINDOWHEIGHT;
#include <iostream>         // std IO
#include <SDL2/SDL.h>       // SDL2
#include "Sprite.h"         // Sprite class for SDL textures
#include "logSDLerr.h"      // error log function


// Window class for SDL window
class Window
{
private:
    float x = 800;                                 // window width
    float y = 600;                                 // window height
    bool flscr = false;                            // if fullscreen
    SDL_Window * winSDL = nullptr;                 // pointer to SDL_Window object
    static SDL_Renderer * render;                  // static pointer to SDL_Renderer object

public:
    Window(float x2, float y2, bool fl): x(x2),y(y2),flscr(fl){}                 // construct Window object
    Window()= default;
    ~Window()                                                                    // destruct Window object cleanup
    {SDL_DestroyWindow( winSDL );SDL_DestroyRenderer(render);}
    [[nodiscard]] float WX()const{return x;}                                     // return width
    [[nodiscard]] float WY()const{return y;}                                     // return height
    //const bool WFL()const{return flscr;}                                       // return true if fullscreen
    SDL_Window * get_win_SDL(){return winSDL;}                                   // return pointer to SDL_Window object
    SDL_Renderer * getrend(){return render;}                                     // return pointer to SDL_Renderer object
    bool Init_SDL();                                                             // initilize SDL video subsystem and create window
    void Close_SDL();                                                            // delocate memory and quit SDL
};


#endif //ARKANOID_GAME_SDL2_WINDOW_H
