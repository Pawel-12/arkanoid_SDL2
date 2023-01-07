//
// Created by Paweł on 29.12.2022.
//

#include "Sprite.h"

// declaration of static variable from class Sprite
SDL_Renderer * Sprite::render = nullptr;

/** \Sprite_class_methods*/

/**\description Sprite object constructor
 * \param rend  pointer to SDL_Renderer
 * \param imgpath path to image file
 * \param vw scale image width to vw percent of WINDOWWIDTH
 * \param vh scale image height to vh percent of half WINDOWHEIGHT
*/
Sprite::Sprite(SDL_Renderer * rend, const char * imgpath, const float& vw, const float& vh )
{
    // assign SDL_Renderer * to static member "render"
    render = rend;

    // Load image to SDL_Texture
    obj = IMG_LoadTexture(rend, imgpath);
    if (obj == nullptr){
        std::cout<<"IMG_LoadTexture: "<<IMG_GetError()<<std::endl;

        //If nullptr try loading image using SDL_Surface
        SDL_Surface *sprite = IMG_Load(imgpath);
        if (sprite == nullptr) {
            logSDLError(std::cout, "SDL_Surface = IMG_Load(imgpath) Error: ");
            return;
        }

        // Upload surface to renderer, and then, free the surface
        obj = SDL_CreateTextureFromSurface(render, sprite);
        SDL_FreeSurface(sprite);
        if (obj == nullptr){
            logSDLError(std::cout, "SDL_CreateTextureFromSurface Error: ");
            return;
        }
    }

    // get the size of texture
    SDL_QueryTexture(obj,nullptr ,nullptr , &width, &height);
    float w = width;
    float h = height;

    // calculate aspect of scaling
    float aspect = w/(WINDOWWIDTH/vw);
    // calculate and round width up
    width = std::ceil(w/aspect);

    // if vh not specified
    if(!vh)
        height = h/aspect;                // calculate height using aspect
    else
        height = ((WINDOWHEIGHT/2)/vh);   //otherwise calculate height using vh
}

/**\description Print Sprite object

*/

 std::ostream & operator<<(std::ostream & os, Sprite & s)
 {
    int w=0;
    int h=0;
    std::string t = "    ";                                                            // separator
    SDL_QueryTexture(s.getobj(),nullptr ,nullptr , &w, &h);     // get Texture size

    os<<"Sprite: {"<<std::endl;

    os<<t<<"\"obj\": {"<<std::endl;
    os<<t+t<<"\"w\": "<<w<<","<<std::endl;
    os<<t+t<<"\"h\": "<<h<<std::endl<<t<<"},\n";

    os<<t<<"\"width\": "<<s.getwidth()<<","<<std::endl;
    os<<t<<"\"height\": "<<s.getheight()<<","<<std::endl;
    os<<t<<"\"render\": "<<s.getrend()<<std::endl<<"}";

    return os;
}