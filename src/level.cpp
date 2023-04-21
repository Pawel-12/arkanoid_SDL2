#include "Level.h"

float WINDOWWIDTH  = 800;
float WINDOWHEIGHT = 600;

Level::Level(Resources * r): res(r)
{
    static int i =1;
    std::cout<<"Level "<<i<<std::endl;
    std::cout<<"Platform speed = "<<res->platform.getspeed()<<std::endl;
    std::cout<<"Ball speed = "<<res->ball.getspeed()<<std::endl;
    i++;

}
Level::~Level() {}

int Level::Tick() {

    static double maxspd     = 2 *   res->conf["platform_speed"];                                  // max platform speed
    static double minspd     = 0.5 * res->conf["platform_speed"];                                // min platform speed
    static double bonusspd   = 0.4 * res->conf["platform_speed"];                                // speed amount added or substracted by ability

    unsigned int start_time = SDL_GetTicks();                                                       // get start time
    SDL_RenderClear(res->window->getrend());                                                // Fill render with color

    res->background.draw();
    res->ball.draw();
    res->platform.draw();

    for(const Entity& e: res->blocks)
    {
        e.draw();
    }
    if(launched)                                                                                // if ball launched
    {
        if (destroyed == res->BLCKNUM)                                                                        // if all blocks are destroyed
        {
            if (res->ball.movexy((res->ball.getxs() ? -1 : 1) * res->ball.getspeed() * modx,
                            (res->ball.getys() ? -1 : 1) * res->ball.getspeed() * mody))      // if not catched ball lost
            {
                launched = false;
                res->ball.hide();
                return 2;
            }
            else {
                if (res->platform.ifcatch(res->ball))                 // if catched ball win
                {
                    //ball.movexy(-1,-5);
                    return 1;
                }
            }

        }
        else
        {
            bool changed = false;                                       // if ball already bounced
            for (Entity &e: res->blocks) {
                if (res->ball.coll(e, changed))                  // check ball collision
                {
                    changed = true;
                    e.hide();                                      // hide block
                    destroyed++;
                    modx = 1;
                    mody = 1;
                }
            }
            if (res->ball.coll(res->platform))                        // check ball collision with platform
            {
                if (res->platform.ifcatch(res->ball))                    // if catchable
                {
                    srand(time(nullptr));
                    if ((rand() % 100) < 15)                     // 15% to catch ball
                    {
                        launched = false;
                        res->ball.setxy(-1, res->platform.gety() - res->ball.getimg()->getheight() - 1);
                    }
                }
            }
            if (res->ball.movexy((res->ball.getxs() ? -1 : 1) * res->ball.getspeed() * modx,(res->ball.getys() ? -1 : 1) * res->ball.getspeed() * mody))        // if not catched ball lost
            {
                launched = false;
                res->ball.hide();
                return 2;
            }

            if (timer_ability >= 5)                // every 5 seconds spawn ability
            {
                int x = rand() % 10;              // random position
                if (rand() % 2) {
                    res->ability_up.unhide();
                    res->ability_up.setxy(x * res->ability_up.getimg()->getwidth(), 0);
                    timer_ability = 0;
                } else {
                    res->ability_down.unhide();
                    res->ability_down.setxy(x * res->ability_down.getimg()->getwidth(), 0);
                    timer_ability = 0;
                }
            }
        }
        if (!res->ability_down.ifhid())                             // move ability if not hidden
        {
            res->ability_down.movey(WINDOWHEIGHT * 0.007);
            res->ability_down.draw();
        }

        if (!res->ability_up.ifhid())                               // move ability if not hidden
        {
            res->ability_up.movey(WINDOWHEIGHT * 0.007);
            res->ability_up.draw();
        }

        if (ability_duration <= 0)                             // reset platform speed if ability ended
            res->platform.setspeed(res->conf["platform_speed"]);

        if (res->platform.ifcatch(res->ability_down))                  // if catched ability
        {
            if ((res->platform.getspeed() - bonusspd) < minspd)
                res->platform.setspeed(minspd);
            else
                res->platform.addspeed(-1 * bonusspd);

            if (ability_duration <= 0)                      // dont add up time
                ability_duration = 20;

            std::cout << res->platform.getspeed() << std::endl;
            res->ability_down.hide();
        }
        if (res->platform.ifcatch(res->ability_up))                   // if catched ability
        {
            if ((res->platform.getspeed() + bonusspd) > maxspd)
                res->platform.setspeed(maxspd);
            else
                res->platform.addspeed(bonusspd);

            if (ability_duration <= 0)                     // dont add up time
                ability_duration = 20;

            std::cout << res->platform.getspeed() << std::endl;
            res->ability_up.hide();
        }
    }
    else                // draw pointer if not launched
    { res->point.draw();}


    SDL_RenderPresent(res->window->getrend());                                               // Show render on window

    if( (1000/60) > (SDL_GetTicks() - start_time) )                                             // 60 FPS
    {
        SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
    }

    timer_ability +=  static_cast<float>( (SDL_GetTicks()-start_time) / 1000.0 );               // add time

    if(ability_duration > 0)
    {
        ability_duration -=  static_cast<float>( (SDL_GetTicks()-start_time) / 1000.0 );        // substract time
    }


    return 0;
}


// param: xrel, yrel: The relative motion in the X/Y direction
// param: x, y : coordinate, relative to window
void Level::onMouseMove(int x, int y, int xrelative, int yrelative){
    if(!launched)
        res->point.setxy(x,y);
}

void Level::onMouseButtonClick(FRMouseButton button, bool isReleased){
    if(button == FRMouseButton::LEFT && isReleased && !launched)
    {
        res->ball.setsigns(res->point.getx()<res->ball.getx(),res->point.gety()<res->ball.gety());
        launched=true;
    }
}

void Level::onKeyPressed(FRKey k, bool isReleased){

    if( !launched )
    {
        if(k == FRKey::RIGHT)
        {
            int r = res->platform.getx();
            res->platform.movex(res->platform.getspeed());
            r -= res->platform.getx();
            res->ball.Entity::movex(r*(-1));
        }
        else if(k == FRKey::LEFT)
        {
            int r = res->platform.getx();
            res->platform.movex(-1 * res->platform.getspeed());
            r -= res->platform.getx();
            res->ball.Entity::movex(r*(-1));
        }
    }

    else if( launched )
    {
        if(k == FRKey::RIGHT)
        {
            res->platform.movex(res->platform.getspeed());
        }
        else if(k == FRKey::LEFT)
        {
            res->platform.movex(-1 * res->platform.getspeed());
        }
    }
}

//void Level::onKeyReleased(FRKey k){}