#include <SDL2/SDL.h>
#include "game.h"

int main(int argc, char* argv[])
{
    return frameworkrun(new Level(), argc, argv);
}