//
// Created by Paweł on 29.12.2022.
//

#ifndef ARKANOID_GAME_SDL2_LOGSDLERR_H
#define ARKANOID_GAME_SDL2_LOGSDLERR_H

#include <iostream>         // std IO
#include <SDL2/SDL.h>       // SDL2
void logSDLError(std::ostream &os, const std::string &msg);       // Log an SDL error with some error message to the output stream of our choice

#endif //ARKANOID_GAME_SDL2_LOGSDLERR_H
