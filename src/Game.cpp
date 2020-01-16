#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"
#include <iostream>

SDL_Renderer* Game::renderer = nullptr;

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

    map = new Map();
    map->init();

    player = new Player(this, map);
    player->setPosition(10,20);

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
                case SDLK_UP:
                    player->move('N');
                    break;
                case SDLK_RIGHT:
                    player->move('E');
                    break;
                case SDLK_DOWN:
                    player->move('S');
                    break;
                case SDLK_LEFT:
                    player->move('W');
                    break;
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
    player->update();
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
    bgRect.w = 640;
    bgRect.h = 480;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 255, 170, 0, 255);
    // render rect
    SDL_RenderFillRect(renderer, &bgRect);


    // draw board
    SDL_Rect outerBoardRect;
    outerBoardRect.x = 150;
    outerBoardRect.y = 120;
    outerBoardRect.w = 340;
    outerBoardRect.h = 340;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &outerBoardRect);

    SDL_Rect innerBoardRect;
    innerBoardRect.x = 160;
    innerBoardRect.y = 130;
    innerBoardRect.w = 320;
    innerBoardRect.h = 320;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xEE, 0xDD, 0xCC, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &innerBoardRect);

    // draw map
    map->render(renderer, 170, 140);

    player->render(renderer, 170, 140);

    // actually render
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    // free memory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    delete player;
    delete map;
}
