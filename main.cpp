//
//
//
#include <SDL2/SDL.h>
#include "main.h"
#include <vector>

float WINDOWWIDTH  = 800;
float WINDOWHEIGHT = 600;

std::vector<int> sprites_ids = {1,41,42,50,58,65,67,68,509};


int main(int argc, char* argv[])
{
    return frameworkrun(new ARKANOID_GAME(), argc, argv);
}