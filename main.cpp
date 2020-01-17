#include <iostream>
#include "Game.h"
#include "SDL.h"

Game *game = NULL;

// screen resolutions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int arg, char* args[])
{

    // cap FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cout << "SDL Error :" << SDL_GetError() << std::endl;
        return 0;
    }

/*
    //start of spiral drawer
    window = SDL_CreateWindow("Spiral Drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "SDL Error :" << SDL_GetError() << std::endl;
        isRunning = false;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    //the seed/first drawer, acts as the parent of all other drawers
    SpiralDrawer seed=new SpiralDrawer(0,0,0,renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
*/
    // initialize game
    std::cout << "Just testing procedurally drawn stuff here" << std::endl;
    game = new Game();
    game->init("Procedural Generation", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (game->running())
    {

        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // game over
    SDL_Delay(3000);
    game->clean();

    delete game;

    return 0;
}
