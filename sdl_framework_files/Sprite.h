//
// Created by Paweł on 29.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_SPRITE_H
#define ARKANOID_GAME_SDL2_SPRITE_H
extern float WINDOWWIDTH;
extern float WINDOWHEIGHT;
#include <iostream>           // std IO
#include <cmath>              // math functions (ceil)
#include <SDL2/SDL.h>         // SDL2
#include <SDL2/SDL_image.h>   // SDL2 loading PNG images
#include "logSDLerr.h"        // error log function


// Sprite class for SDL textures
class Sprite
{
private:
    SDL_Texture * obj;                            // pointer to SDL_Texture object
    int width;                                    // sprite width
    int height;                                   // sprite height
    static SDL_Renderer * render;                 // static pointer to SDL_Renderer object

public:
    Sprite() = default;
    ~Sprite(){SDL_DestroyTexture(obj);}          // destruct Sprite object cleanup
    Sprite(Sprite&& s)                                  // move constructor
    {
        width = s.width;
        height = s.height;
        obj = s.obj;

        s.obj = nullptr;
    }
    Sprite(Sprite & s)                                 // copy constructor
    {
        width = s.width;
        height = s.height;
        obj = s.obj;

        s.obj = nullptr;
    }
    Sprite & operator=(const Sprite & s)               // assignment operator
    {
        if(this == &s)                                 // protect against invalid self-assignment
            return *this;
        width = s.width;
        height = s.height;

        SDL_Surface * temp;                                                     // temp Surface
        SDL_LockTextureToSurface(s.obj,NULL, &temp);         // copy Texture to temp Surface
        obj = SDL_CreateTextureFromSurface(render,temp);         // construct new Texture from temp Surface
        SDL_FreeSurface(temp);                                           //  free temp Surface
        return *this;
    }
    Sprite(SDL_Renderer * rend, const char * imgpath, const float& vw = WINDOWWIDTH, const float& vh = 0 );       // construct Sprite object
    [[nodiscard]] int getwidth()const{return width;}             // return width
    [[nodiscard]] int getheight()const{return height;}           // return height
    void setwh(unsigned int w, unsigned int h)                                     // set width and height
    {
        width  = w;
        height = h;
    }
    SDL_Texture * getobj(){return obj;}                          // return pointer to SDL_Texture object
    SDL_Renderer * getrend(){return render;}                     // return pointer to SDL_Renderer object

    friend std::ostream & operator<<(std::ostream & os, Sprite & s);    // print Sprite object
};


#endif //ARKANOID_GAME_SDL2_SPRITE_H
