#include "TextureManager.h"

#include <iostream>

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* fileName)
{
    SDL_Surface* tmpSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // clean
    SDL_FreeSurface(tmpSurface);

    return texture;
}


void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::DrawTilt(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int tilt)
{
    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (tilt == 90)
    {
        angle = 90;
    }
    else if (tilt == 180)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (tilt == 270)
    {
        angle = 90;
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_RenderCopyEx(renderer, tex, &src, &dest, angle, NULL, flip );

    /*std::cout << "Reporting SDL_Error() : " << SDL_GetError() << std::endl;
    std::cout << "Reporting tilt : " << tilt << std::endl;
    std::cout << "Reporting angle : " << angle << std::endl;
    std::cout << "Reporting flip : " << flip << std::endl;*/
}
