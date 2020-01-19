#include "Game.h"
#include "OldEntity.h"
#include <iostream>


SDL_Renderer* Game::renderer = nullptr;

//Entity entities[10];
OldEntity entity;

Game::Game()
{

}

Game::~Game()
{

}

bool Game::running() { return isRunning; }

void Game::init(const char* title, int width, int height)
{
    // create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "SDL Error :" << SDL_GetError() << std::endl;
        isRunning = false;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    entity = new OldEntity();
    entity->init();

    std::cout << "Genesis " << ": x=" << entity->xPos << " / y=" << entity->yPos
            << " / xV=" << entity->xVel << " / yV=" << entity->yVel << std::endl;

    isRunning = true;

    // render at init to show current board with number indexes
    render();
}

void Game::handleEvents()
{
    //std::cout << "Polling events..." << std::endl;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
                switch( event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                }
            break;

        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    entity->update();
}

void Game::render()
{
    // clear frame
    SDL_RenderClear(renderer);

    // render background and board
    // draw background
    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.w = MAP_WIDTH;
    bgRect.h = MAP_HEIGHT;
    // set current renderer color
    int tmpColor = SDL_GetTicks() % 120;
    SDL_SetRenderDrawColor(renderer, 120, 120, 120+tmpColor, 255);
    // render rect
    SDL_RenderFillRect(renderer, &bgRect);

    entity->render(renderer);

    // actually render
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    // free memory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    delete entity;
    //delete map;
}
