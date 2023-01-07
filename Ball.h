//
// Created by Paweł on 05.01.2023.
//

#ifndef ARKANOID_GAME_SDL2_BALL_H
#define ARKANOID_GAME_SDL2_BALL_H

class Ball :public Entity
{
private:
    bool xs;
    bool ys;
    double speed = 0.0035 * WINDOWWIDTH;
public:
    Ball(Sprite * img2, const int & x2, const int & y2, const int & id2): Entity(img2,x2,y2,id2)  { };
    Ball(){}
    virtual ~Ball(){};
    bool getxs()const
    {
        return xs;
    }
    bool getys()const
    {
        return ys;
    }
    double getspeed()const
    { return speed;}
    void setspeed(double s)
    { speed = s;}
    void setsigns(bool xsign, bool ysign)
    {
        xs = xsign;
        ys = ysign;
    }

    bool coll(const  Entity& block, bool changed = false)
    {
        if(block.ifhid())
            return false;
        int r  = (getimg()->getwidth())/2;
        int ry = (getimg()->getheight())/2;

        int midx = getx() + r;
        int midy = gety() + ry;

        int blockx = block.getx();
        int blocky = block.gety();

        int blockw = block.getimg()->getwidth();
        int blockh = block.getimg()->getheight();


        bool between_y = ((midy >= blocky - ry) && (midy <= blocky + ry + blockh));
        bool between_x = ((midx >= blockx - r)  && (midx <= blockx + r + blockw));

        //bool left  = ((midx >= blockx - r) && (midx <= blockx + r));
        bool left  = ((midx >= blockx - r) && (midx <= blockx));
        bool right = ((midx <= blockx + r + blockw) && (midx >= blockx + blockw));

        bool top   = ((midy >= blocky - ry) && (midy <= blocky));
        bool bot   = ((midy <= blocky + ry + blockh) && (midy >= blocky + blockh));

        if((left||right) && between_y)
        {
            if(!changed)
            {
                xs = !xs;
                ys = !ys;
            }
            return true;
        }
        else if((top||bot) && between_x)
        {
            if(!changed)
            {
                ys = !ys;
            }
            return true;
        }
        else
            return false;
    }
    bool movexy(const int & a, const int & b)
    {
        if(getx() + a <= 0)
        {
            setxy(0, -1);
            xs = !xs;
        }
        else if((getx() + (getimg()->getwidth()) + a) >= WINDOWWIDTH)
        {
            setxy(WINDOWWIDTH - getimg()->getwidth(), -1);
            xs = !xs;
        }
        else
            setxy(getx() + a, -1);

        if(b)
        {
            if(gety() + b <= 0)
            {
                setxy(-1, 0);
                ys = !ys;
            }
            else if((gety() + getimg()->getheight() + b) >= WINDOWHEIGHT)
            {
                return true;
            }
            else
                setxy(-1, gety() + b);
        }

        return false;
    }
};

#endif //ARKANOID_GAME_SDL2_BALL_H
