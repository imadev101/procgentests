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
    const int FPS = 4;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cout << "SDL Error :" << SDL_GetError() << std::endl;
        return 0;
    }

    // initialize game
    std::cout << "Welcome to Pacman Game" << std::endl;
    game = new Game();
    game->init("Pacman", SCREEN_WIDTH, SCREEN_HEIGHT);

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
