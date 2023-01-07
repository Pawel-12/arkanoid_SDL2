//
// Created by Paweł on 29.12.2022.
//
#include "Window.h"

// declaration of static variable from class Window
SDL_Renderer * Window::render = nullptr;

/**\Window_class_methods*/

/** \Description function to initilize SDL video subsystem and create window
 * \returns false if initialization or window creation failed, true otherwise*/
bool Window::Init_SDL()
{
    //Initialize SDL subsystems
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        logSDLError(std::cout, "SDL could not initialize! SDL_Error: ");
        return false;
    }

    else
    {
        // Create window
        if (flscr)
         winSDL = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        else
         winSDL = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);

        // if create window failed
        if( winSDL == nullptr )
        {
            logSDLError(std::cout, "Window could not be created! SDL_Error: ");
            return false;
        }

        // create SDL renderer
        render = SDL_CreateRenderer(winSDL, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);

        // if create renderer failed
        if (render == nullptr)
        {
            logSDLError(std::cout, "SDL_CreateRenderer Error:");
            return false;
        }

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);          // Set renderer color
        SDL_RenderClear(render);                                          // Fill renderer with color
        SDL_RenderPresent(render);                                        // Show renderer on window

        //Initialize SDL_image subsystems
         if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            std::cout<<"IMG_INIT: "<<IMG_GetError()<<std::endl;
            return false;
        }

    }
    return true;
}

/** \Description function to delocate memory and quit SDL*/
void Window::Close_SDL()
{
    //Destroy window
    SDL_DestroyWindow( winSDL );
    winSDL = nullptr;

    // destroy renderer
    SDL_DestroyRenderer(render);
    render = nullptr;

    //Quit SDL IMG
    IMG_Quit();

    //Quit SDL subsystems
    SDL_Quit();

}
