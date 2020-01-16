#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* fileName);
        static void Draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
        static void DrawTilt(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int tilt);

    protected:

    private:
};

#endif // TEXTUREMANAGER_H
