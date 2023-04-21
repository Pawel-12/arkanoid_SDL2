//
// Created by Pawel on 11.01.2023.
//

#ifndef ARKANOID_GAME_SDL2_RESOURCES_H
#define ARKANOID_GAME_SDL2_RESOURCES_H

#include "sdl_framework_files/sdl_framework.h"
#include "Ball.h"
#include "Platform.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_map>
const std::vector<int> sprites_ids = {1,41,42,50,58,65,67,68,509};


class Resources {
private:
    Window * window;
    Entity background;
    Entity point;
    Entity ability_up,ability_down;
    Ball ball;
    Platform platform;
    std::unordered_map<std::string, float> conf;
    std::unordered_map<int, Sprite> sprites;
    unsigned int COLS = 5;
    unsigned int ROWS = 5;
    unsigned int BLCKNUM = COLS*ROWS;
    friend class Level;
    std::vector<Entity> blocks;
    void startsetup()
    {
        int iter = 0;
        for(;iter < BLCKNUM; iter++ )
        {
            int s = conf["blockSprite"];
            int w = sprites[s].getwidth();
            int h = sprites[s].getheight() ;
            blocks.emplace_back( &sprites[s], (iter%COLS) * w, (iter/ROWS) * h, iter );
        }

        Sprite *  p_plat  = &sprites [  conf["platformSprite"]     ];           // pointer to sprite for platform
        Sprite *  p_ball  = &sprites [  conf["ballSprite"]         ];           // pointer to sprite for ball
        Sprite *  p_back  = &sprites [  conf["backgroundSprite"]   ];           // pointer to sprite for background
        Sprite *  p_abdw  = &sprites [  conf["abilitydownSprite"] ];           // pointer to sprite for abilitydown
        Sprite *  p_abup  = &sprites [  conf["abilityupSprite"]   ];           // pointer to sprite for abilityup

        const int halfWplat = p_plat->getwidth()/2;             // half platform width
        const int halfWball = p_ball->getwidth()/2;             // half ball width
        const int Hplat     = p_plat->getheight();              // platform height
        const int Hball     = p_ball->getheight();              // ball height

        platform = Platform( p_plat, (WINDOWWIDTH/2) - halfWplat, WINDOWHEIGHT - Hplat, iter, &ball );
        ball     = Ball( p_ball, platform.getx() - halfWball + halfWplat - 1, WINDOWHEIGHT - Hplat - Hball - 1, iter + 1);
        point    = Entity( p_ball, 0, 0, iter + 2 );

        background = Entity( p_back, 0, 0, iter + 3 );
        ability_down = Entity( p_abdw, 0, 0, iter + 6);
        ability_up   = Entity( p_abup, 0, 0, iter + 7);

        ability_down.hide();
        ability_up.hide();

        SDL_ShowCursor(SDL_DISABLE);

        conf["ball_speed"] *= WINDOWWIDTH;
        ball.setspeed(conf["ball_speed"]);

        conf["platform_speed"] *= WINDOWWIDTH;
        platform.setspeed(conf["platform_speed"]);
    }
    void reset()
    {
        int iter = 0;
        for(;iter < BLCKNUM; iter++ )
        {
            int s = conf["blockSprite"];
            int w = sprites[s].getwidth();
            int h = sprites[s].getheight() ;
            blocks.emplace_back( &sprites[s], (iter%COLS) * w, (iter/ROWS) * h, iter );
        }

        Sprite *  p_plat  = &sprites [  conf["platformSprite"]     ];           // pointer to sprite for platform
        Sprite *  p_ball  = &sprites [  conf["ballSprite"]         ];           // pointer to sprite for ball

        const int halfWplat = p_plat->getwidth()/2;             // half platform width
        const int halfWball = p_ball->getwidth()/2;             // half ball width
        const int Hplat     = p_plat->getheight();              // platform height
        const int Hball     = p_ball->getheight();              // ball height

        platform.setxy((WINDOWWIDTH/2) - halfWplat, WINDOWHEIGHT - Hplat );
        ball.setxy(platform.getx() - halfWball + halfWplat - 1, WINDOWHEIGHT - Hplat - Hball - 1);

        ball.unhide();
        platform.unhide();
        background.unhide();

        ability_down.hide();
        ability_up.hide();

        SDL_ShowCursor(SDL_DISABLE);

        conf["ball_speed"] *= 1.05;                     // every level ball speed up 2 percent
        ball.setspeed(conf["ball_speed"]);           // set new speed
        platform.setspeed(conf["platform_speed"]);   // set base speed
    }
public:
    Resources(){
        window = new Window();
    }
    ~Resources() {
        window->Close_SDL();
        delete window;
    }

    bool LoadConfig() {                     // read config from text file, returns false if failed, true otherwise
        std::ifstream fconfig;
        fconfig.open("../config_file.txt");                         // open file

        if (!fconfig)
        {
            std::cerr << "config_file.txt could not be opened for reading!\n";
            return false;
        }

        std::string strInput;

        while (fconfig && std::getline(fconfig, strInput) )        // read lines until file end
        {
            std::string part1{},part2{};
            std::istringstream iss{ strInput };
            std::getline(iss, part1, '=');                   // get string until '='
            if(part1.back() == ' ')                                      // trim if necessary
                part1.pop_back();

            if (!std::getline(iss, part2))                        // get second part
                break;

            conf.insert({part1, std::stof(part2)});        // insert into unordered_map
        }

        fconfig.close();                                                // close file

        COLS = conf["COLS"];
        ROWS = conf["ROWS"];
        BLCKNUM = COLS * ROWS;

        window->setsize(conf["WINDOWWIDTH"], conf["WINDOWHEIGHT"], conf["FULLSCREEN"]);
        WINDOWWIDTH  = conf["WINDOWWIDTH"];
        WINDOWHEIGHT = conf["WINDOWHEIGHT"];

        return true;
    }


    bool Init(const int & argc, char* argv[]){
        // init SDL
        if(!window->Init_SDL())
        {
            window->Close_SDL();
            delete window;
            return false;
        }
        else
        {
            srand(time(nullptr));

            Handle_Console_Args(*window, argc, argv);

            for(int i: sprites_ids) {
                std::string s;

                if (i < 10)
                    s = "../data/0" + std::to_string(i) + "-Breakout-Tiles.png";
                else
                    s = "../data/" + std::to_string(i) + "-Breakout-Tiles.png";

                const char *pchar = s.c_str();

                // insert sprite id and Sprite object into unordered_map
                switch (i) {
                    case 50:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, 5.0));
                        break;
                    case 509:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, (WINDOWWIDTH / sprites[50].getheight() ), (WINDOWHEIGHT / sprites[50].getwidth())/2));
                        break;

                    case 58:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, 33.0));
                        break;

                    case 65:
                    case 67:
                    case 68:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, 1, 0.5));
                        break;
                    case 41:
                    case 42:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, 10));
                        break;
                    default:
                        sprites.emplace(i, Sprite(window->getrend(), pchar, COLS, ROWS));
                }

                std::cout<<pchar<<" loaded"<<std::endl;
                std::cout<<sprites[i]<<std::endl;
            }

            startsetup();

            return true;
        }
    }

    void nextlevel()
    {
        COLS++;
        ROWS++;
        conf["COLS"]++;
        conf["ROWS"]++;
        BLCKNUM = COLS*ROWS;
        blocks.clear();
        int w = 0;
        int h = 0;
        SDL_QueryTexture(sprites[ conf["blockSprite"]].getobj(),nullptr ,nullptr , &w, &h);     // get Texture size

        w = std::ceil(WINDOWWIDTH/COLS);

            h = std::ceil((WINDOWHEIGHT/2)/ROWS);
        sprites[ conf["blockSprite"]].setwh(w,h);
        reset();
    }
};


#endif //ARKANOID_GAME_SDL2_RESOURCES_H
