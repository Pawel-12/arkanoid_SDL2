#pragma once

class Platform :public Entity
{
private:
    Ball* ball;
    double speed = WINDOWWIDTH * 0.035;
public:
    Platform(Sprite * img2, const int & x2, const int & y2, const int & id2, Ball*  ball2): Entity(img2,x2,y2,id2),ball(ball2) { };
    Platform(){}
    double getspeed()const
    { return speed;}
    void setspeed(double s)
    { speed = s;}
    void addspeed(double s)
    { speed += s;}
    virtual ~Platform (){};
    virtual void movex(const int & a)
    {
        if(collball(a))
        {
            ball->setspeed(ball->getspeed()*1.1);
        }
        else
        {
            if(getx() + a < 0)
                setxy(0, -1);

            else if((getx() + (getimg()->getwidth()) + a) > WINDOWWIDTH)
                setxy(WINDOWWIDTH - getimg()->getwidth(), -1);

            else
                setxy(getx() + a, -1);
        }

    }

    bool collball(const int & num)
    {
        int r  = ((ball->getimg()->getwidth())/2);
        int ry = ((ball->getimg()->getheight())/2);
        int xtest = getx() + num;

        bool Y = ((ball->gety() + ry >= gety() - ry))&& (ball->gety() + ry <= gety() + getimg()->getheight());
        bool L = (ball->getx() + r >= xtest - r) && (ball->getx() + r <= xtest);
        bool P = (ball->getx() + r <= xtest + getimg()->getwidth() + r) && (ball->getx() + r >= xtest + getimg()->getwidth());
        bool LP = (ball->getx() + r >= xtest - r) && (ball->getx() + r <= xtest + getimg()->getwidth() + r);

        if((LP) && Y)
            return true;
        else
            return false;
    }


    bool ifcatch(const Entity & e)
    {
        if(e.ifhid())
            return false;
        int r  = ((e.getimg()->getwidth())/2);
        int ry = ((e.getimg()->getheight())/2);

        int midx = e.getx() + r;
        int midy = e.gety() + ry;

        int blockx = getx();
        int blocky = gety();

        int blockw = getimg()->getwidth();


        bool top       = ((midy >= blocky - ry) && (midy <= blocky));
        bool between_x = ((midx >= blockx - r) && (midx <= blockx + r + blockw));

        if(top && between_x)
            return true;
        else
            return false;
    }
};