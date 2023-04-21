//
// Created by Paweł on 27.12.2022.
//

#include "sdl_framework.h"

/**\description function to handle console arguments
 * \param w  a reference to Window
 * \param argc number of arguments
 *
 * \param argv  an array of char* arguments
 * \returns false if there was no arguments, true otherwise

*/
bool Handle_Console_Args(Window & w, const int & argc, char* argv[] )
{
    // if no args return false
    if(argc < 2)
        return false;

    // command -w 1920x1080
    bool FLSCR = false;           // if fullscreen

    int i = 1;
    // get the first argument
    std::string s = argv[i];

    // if flag = -window or -w, and next argument exists and starts with digit
    if(((s == "-window") || (s == "-w")) && argc-(i+1) >= 1 && std::isdigit(argv[i+1][0]))
        {
            std::string::size_type sz;
            s = argv[i+1];
            // get first number until char separator e.g. '1920'x1080
            WINDOWWIDTH = std::stoi(s,&sz);

            // if there is more digits, get second number after char separator e.g. 1920x'1080'
            if(sz != s.size())
            WINDOWHEIGHT = std::stoi(s.substr(sz+1));

            // if there is third numeric value
           if(argc-(i+1) >= 2 && std::isdigit(argv[i+2][0]))
            {
                FLSCR = std::stoi(argv[i+2]);
                i = i+2;
            }
        }

    // assign values to Window
    w.setsize(WINDOWWIDTH, WINDOWHEIGHT, FLSCR);
    return true;
}

/*int frameworkrun(SDL_Framework * f, const int & argc, char* argv[]){

    if(!f->LoadConfig())
        return 0;
    
    if(!f->Init( argc, argv))
        return 0;

    SDL_Event e;
    bool quit = false;

    while (!quit){
        while (SDL_PollEvent(&e)){

            if (e.type == SDL_QUIT)
                quit = true;

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

        if(quit){
            delete f;
            return 11;
        }
        quit=f->Tick();
    }

    delete f;
    return 12;

}*/