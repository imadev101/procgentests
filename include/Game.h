#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"

// predeclaration
class Map;
class Entity;


class Game
{
    public:
        Game();
        virtual ~Game();

        void init(const char* title, int width, int height);
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();

        static SDL_Renderer *renderer;
        SDL_Window* window;
        SDL_Event event;

        Map *map;
        Entity *entity;

        static const int MAP_WIDTH = 640;
        static const int MAP_HEIGHT = 480;

    protected:

    private:
        bool isRunning;

};

#endif // GAME_H
