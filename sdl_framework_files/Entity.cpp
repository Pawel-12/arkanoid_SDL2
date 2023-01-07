//
// Created by Paweł on 29.12.2022.
//

#include "Entity.h"

/** \Entity_class_methods*/

/**\description copy sprite texture to renderer, if it isnt hidden
*/
void Entity::draw()const
{
    // if not hidden
    if(!hidden)
    {
        SDL_Rect rect {x, y, img->getwidth(), img->getheight() };                            // create rect with size of sprite
        SDL_RenderCopy(img->getrend(), img->getobj(), nullptr, &rect); // Copy the texture into render
    }
}

/**\description set Entity location on x and y axis
 * \param x2  location on x axis  x2>=0
 * \param y2  location on y axis  y2>=0
*/
void Entity::setxy(const int& x2, const int& y2)
{
    if(x2 >= 0)         // if x2 >= 0 set x value
        x = x2;

    if(y2 >= 0)         // if y2 >= 0 set y value
        y = y2;

}

/**\description move Entity on x axis
 * \param a  pixel amount,  if a\<0 moves left  if a>0 moves right

*/

void Entity::movex(const int& a)
{   //if not hidden and a != 0
    if(a && !ifhid()) {
        if (x + a < 0)                                       // if x+a lower than left window border
            x = 0;
        else if ((x + (img->getwidth()) + a) > WINDOWWIDTH)  // if x+imgwidth+a higher than right window border
            x = WINDOWWIDTH - img->getwidth();
        else
            x += a;
    }
}

/**\description move Entity on y axis
 * \param a  pixel amount,  if a\<0 moves up  if a>0 moves down

*/
//moving powerups
 void Entity::movey(const int& a)
{   //if not hidden and a != 0
    if(a && !ifhid()) {
        if ((y + (img->getheight()) + a) > WINDOWHEIGHT)
            (*this).hide();
        else {
            y += a;
        }
    }
}

/**\description Print Entity object

*/

 std::ostream & operator<<(std::ostream & os, const Entity & en)
 {
    std::string t = "    ";                                                            // separator
    os<<"Entity: {"<<std::endl;

    os<<*(en.getimg())<<","<<std::endl;
    os<<t<<"\"x\": "<<en.getx()<<","<<std::endl;
    os<<t<<"\"y\": "<<en.gety()<<","<<std::endl;
    os<<t<<"\"id\": "<<en.getid()<<","<<std::endl;
    os<<t<<"\"hidden\": "<<en.ifhid()<<"\n},"<<std::endl;

    return os;
}
