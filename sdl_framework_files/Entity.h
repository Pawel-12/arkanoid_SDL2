//
// Created by Paweł on 29.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_ENTITY_H
#define ARKANOID_GAME_SDL2_ENTITY_H
extern float WINDOWWIDTH;
extern float WINDOWHEIGHT;
#include <iostream>         // std IO
#include "Sprite.h"         // Sprite class for SDL textures
#include "logSDLerr.h"      // error log function

// Entity class for program entities
class Entity
{
private:
    Sprite* img;                                   // pointer to Sprite object (containing SDL_Texture pointer)
    int x;                                         // location on x axis
    int y;                                         // location on y axis
    int id;                                        // id of entity
    bool hidden=false;                             // if hidden (should be displayed in window or not)

public:
    Entity()= default;
    virtual ~Entity(){};                                                                                     // virtual destructor
    Entity(Sprite * img2, const int& x2, const int& y2, const int& id2): img(img2),x(x2),y(y2),id(id2){};    // construct Entity object
    [[nodiscard]] int getx()const{return x;}                                                                 // return location on x axis
    [[nodiscard]] int gety()const{return y;}                                                                 // return location on y axis
    [[nodiscard]] int getid()const{return id;}                                                               // return id of entity
    [[nodiscard]] bool ifhid()const{return hidden;}                                                          // return true if object is hidden
    [[nodiscard]] Sprite* getimg()const{return img;}                                                         // return pointer to Sprite object (containing SDL_Texture pointer)

    void setxy(const int& x2, const int& y2);      // set Entity location on x and y axis
    void hide(){hidden=true;}                      // hide object
    void unhide(){hidden=false;}                   // unhide object
    void draw()const;                              // copy sprite texture to renderer, if it isnt hidden

    virtual void movex(const int& a);              // move Entity on x axis
    virtual void movey(const int& a);              // move Entity on y axis

    friend std::ostream & operator<<(std::ostream & os, const Entity & en);     // print Entity object
};



#endif //ARKANOID_GAME_SDL2_ENTITY_H
