#include "game.h"

int frameworkrun(Level * f, const int & argc, char* argv[])
{

    Resources resources;
    if(!resources.LoadConfig())
        return 0;

    if(!resources.Init( argc, argv))
        return 0;

    SDL_Event e;
    int quit = 0;
    *f = Level(&resources);

    while (quit != 2){
        while (SDL_PollEvent(&e)){

            if (e.type == SDL_QUIT)
                quit = 2;

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

        if(quit == 2){
            delete f;
            f = nullptr;
            return 11;
        }
        else if(quit == 1)
        {
            delete f;
            resources.nextlevel();
            f = new Level(&resources);
            quit = 0;
        }
        quit = f->Tick();
    }

    delete f;
    f = nullptr;
    return 12;

}

/*#include "game.h"

float WINDOWWIDTH  = 800;
float WINDOWHEIGHT = 600;


    ARKANOID_GAME::ARKANOID_GAME(){
        window = new Window();
    }
    ARKANOID_GAME::~ARKANOID_GAME() {
        window->Close_SDL();
        delete window;
    }

     bool ARKANOID_GAME::LoadConfig() {                     // read config from text file, returns false if failed, true otherwise
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


     bool ARKANOID_GAME::Init(const int & argc, char* argv[]){
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


            int iter = 0;
            for(;iter < BLCKNUM; iter++ )
            {
                int s = conf["blockSprite"];
                int w = sprites[s].getwidth();
                int h = sprites[s].getheight() ;
                blocks.emplace_back( &sprites[s], (iter%COLS) * w, (iter/COLS) * h, iter );
            }

            Sprite *  p_plat  = &sprites [  conf["platformSprite"]     ];           // pointer to sprite for platform
            Sprite *  p_ball  = &sprites [  conf["ballSprite"]         ];           // pointer to sprite for ball
            Sprite *  p_back  = &sprites [  conf["backgroundSprite"]   ];           // pointer to sprite for background
            Sprite *  p_winn  = &sprites [  conf["winSprite"]   ];           // pointer to sprite for win background
            Sprite *  p_lost  = &sprites [  conf["lostSprite"]   ];           // pointer to sprite for lost background
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
            loseback   = Entity( p_lost, 0, 0, iter + 4 );
            winback    = Entity( p_winn, 0, 0, iter + 5 );

            ability_down = Entity( p_abdw, 0, 0, iter + 6);
            ability_up   = Entity( p_abup, 0, 0, iter + 7);

            ability_down.hide();
            ability_up.hide();

            SDL_ShowCursor(SDL_DISABLE);

            conf["ball_speed"] *= WINDOWWIDTH;
            ball.setspeed(conf["ball_speed"]);

            conf["platform_speed"] *= WINDOWWIDTH;
            platform.setspeed(conf["platform_speed"]);

            return true;
        }
    }

     int ARKANOID_GAME::Tick() {

        static double maxspd     = 2 * conf["platform_speed"];                                  // max platform speed
        static double minspd     = 0.5 * conf["platform_speed"];                                // min platform speed
        static double bonusspd   = 0.4 * conf["platform_speed"];                                // speed amount added or substracted by ability

        unsigned int start_time = SDL_GetTicks();                                                       // get start time
        SDL_RenderClear(window->getrend());                                                    // Fill render with color
        background.draw();

        if(destroyed == BLCKNUM)                                                                        // if all blocks are destroyed
        {
            if(launched)                                                                                // if ball launched
            {
                if(!win && ball.movexy( (ball.getxs()?-1:1) * ball.getspeed() * modx, (ball.getys()?-1:1) * ball.getspeed() * mody))      // if not catched ball lost
                {
                    background = loseback;
                    lost       = true;
                    launched   = false;
                    ball.hide();
                }
                else if(!win)
                {

                    if( platform.ifcatch(ball) )                 // if catched ball win
                    {
                        win = true;
                        //ball.movexy(-1,-5);
                        background = winback;
                    }
                }
            }
        }
        else if(launched && !lost)                                  // if launched and not lost
        {
            bool changed = false;                                       // if ball already bounced
            for(Entity &e: blocks)
            {
                if (ball.coll(e,changed) )                  // check ball collision
                {
                    changed = true;
                    e.hide();                                      // hide block
                    destroyed++;
                    modx = 1;
                    mody = 1;
                }
            }
            if(ball.coll(platform))                        // check ball collision with platform
            {
                if(platform.ifcatch(ball))                    // if catchable
                {
                    srand(time(nullptr));
                    if( (rand() % 100) < 15)                     // 15% to catch ball
                    {
                        launched = false;
                        ball.setxy(-1, platform.gety() - ball.getimg()->getheight() - 1);
                    }
                }
            }
            if(ball.movexy((ball.getxs()?-1:1) * ball.getspeed() * modx, (ball.getys()?-1:1) * ball.getspeed() * mody))        // if not catched ball lost
            {
                background = loseback;
                lost       = true;
                launched   = false;
                ball.hide();
            }

            if(timer_ability >= 5)                // every 5 seconds spawn ability
            {
                int x = rand()%10;              // random position
                if( rand()%2 )
                {
                    ability_up.unhide();
                    ability_up.setxy(x * ability_up.getimg()->getwidth(), 0);
                    timer_ability = 0;
                }
                else
                {
                    ability_down.unhide();
                    ability_down.setxy(x * ability_down.getimg()->getwidth(), 0);
                    timer_ability = 0;
                }
            }
        }
        if( !ability_down.ifhid() )                             // move ability if not hidden
        {
            ability_down.movey(WINDOWHEIGHT * 0.007);
            ability_down.draw();
        }

        if( !ability_up.ifhid() )                               // move ability if not hidden
        {
            ability_up.movey(WINDOWHEIGHT * 0.007);
            ability_up.draw();
        }

        if( ability_duration <= 0 )                             // reset platform speed if ability ended
            platform.setspeed(conf["platform_speed"]);

        if(platform.ifcatch(ability_down))                  // if catched ability
        {
            if( (platform.getspeed() - bonusspd) < minspd )
                platform.setspeed(minspd);
            else
                platform.addspeed(-1 * bonusspd);

            if(ability_duration <= 0)                      // dont add up time
                ability_duration = 20;

            std::cout<<  platform.getspeed()  <<std::endl;
            ability_down.hide();
        }
        if(platform.ifcatch(ability_up))                   // if catched ability
        {
            if( (platform.getspeed() + bonusspd) > maxspd )
                platform.setspeed(maxspd);
            else
                platform.addspeed(bonusspd);

            if(ability_duration <= 0)                     // dont add up time
                ability_duration = 20;

            std::cout<<  platform.getspeed()  <<std::endl;
            ability_up.hide();
        }

        ball.draw();

        platform.draw();

        for(const Entity& e: blocks)
        {
            e.draw();
        }

        if(!launched && !lost)                // draw pointer if not launched
        {
            point.draw();
        }

        if(win||lost)                        // draw background after win/lost
        {
            background.draw();
        }

        SDL_RenderPresent(window->getrend());                                               // Show render on window

        if( (1000/60) > (SDL_GetTicks() - start_time) )                                             // 60 FPS
        {
            SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
        }

        timer_ability +=  static_cast<float>( (SDL_GetTicks()-start_time) / 1000.0 );               // add time

        if(ability_duration > 0)
        {
            ability_duration -=  static_cast<float>( (SDL_GetTicks()-start_time) / 1000.0 );        // substract time
        }

        if(win||lost)                                                                                // close game after 3 seconds if win/lost
        {
            timer += static_cast<float>( (SDL_GetTicks()-start_time) / 1000.0);
            if(timer >= 3)
                return true;
        }
        return false;
    }




    // param: xrel, yrel: The relative motion in the X/Y direction
    // param: x, y : coordinate, relative to window
     void ARKANOID_GAME::onMouseMove(int x, int y, int xrelative, int yrelative){
        if(!launched)
            point.setxy(x,y);
    }

     void ARKANOID_GAME::onMouseButtonClick(FRMouseButton button, bool isReleased){
        if(button == FRMouseButton::LEFT && isReleased && !launched)
        {
            ball.setsigns(point.getx()<ball.getx(),point.gety()<ball.gety());
            launched=true;
        }
    }

     void ARKANOID_GAME::onKeyPressed(FRKey k, bool isReleased){

        if( !launched || win)
        {
            if(k == FRKey::RIGHT)
            {
                int r = platform.getx();
                platform.movex(platform.getspeed());
                r -= platform.getx();
                ball.Entity::movex(r*(-1));
            }
            else if(k == FRKey::LEFT)
            {
                int r = platform.getx();
                platform.movex(-1 * platform.getspeed());
                r -= platform.getx();
                ball.Entity::movex(r*(-1));
            }
        }

        else if( launched )
        {
            if(k == FRKey::RIGHT)
            {
                platform.movex(platform.getspeed());
            }
            else if(k == FRKey::LEFT)
            {
                platform.movex(-1 * platform.getspeed());
            }
        }
    }
     void ARKANOID_GAME::onKeyReleased(FRKey k){}
*/