#include "Player.h"
#include "Map.h"
#include "TextureManager.h"

SDL_Texture *texture = NULL;
bool animated = false;
int frames = 6;
int speed = 250;

int tilt = 0;

Player::Player(Game *mGame, Map *mMap)
{
    //ctor
    game = mGame;
    map = mMap;
    name = "JOE";
    texture = TextureManager::LoadTexture(Game::renderer, "images/player.png");
}

Player::~Player()
{
    //dtor
}

void Player::move(char direction)
{
    int xMod = 0;
    int yMod = 0;
    int tmpTilt = 0;
    switch (direction)
    {
    case 'N':
        yMod = -1; // our zero y is north
        tmpTilt = 90;
        break;
    case 'E':
        xMod = 1;
        tmpTilt = 180;
        break;
    case 'S':
        yMod = 1;
        tmpTilt = 270;
        break;
    case 'W':
        xMod = -1;
        tmpTilt = 0;
        break;
    }
    // using modulo allow to round up around map
    int testX = (xPos+xMod)%map->width;
    // modulo is weird with negative number
    if (testX < 0) { testX = map->width; }
    int testY = (yPos+yMod)%map->height;
    if (testY < 0) { testY = map->height; }

    if (map->canWalk(testX, testY))
    {
        xVel = xMod;
        yVel = yMod;
        tilt = tmpTilt;
    }
}

void Player::render(SDL_Renderer *renderer, int xPosRender, int yPosRender)
{
    int multiplier = 1;
    SDL_Rect playerRect;
    playerRect.x = xPosRender + xPos*10*multiplier - 3*multiplier;
    playerRect.y = yPosRender + yPos*10*multiplier - 3*multiplier;
    playerRect.w = 16*multiplier;
    playerRect.h = 16*multiplier;

    SDL_Rect srcRect;
    srcRect.x = 0;
    int frameNumber = (SDL_GetTicks()/speed) % frames; // will get 1 frame per tick
    std::cout << "Frame number is " << frameNumber << "at tick " << SDL_GetTicks() << std::endl;
    srcRect.y = frameNumber * 16;
    srcRect.w = 16;
    srcRect.h = 16;

    // drawing player with a tilt in clockwise deg
    TextureManager::DrawTilt(renderer, texture, srcRect, playerRect, tilt);

    SDL_Delay(100);

}

void Player::update()
{
        // using modulo allow to round up around map
    int testX = (xPos+xVel)%map->width;
    if (testX < 0) { testX = map->width + xVel; }
    int testY = (yPos+yVel)%map->height;
    if (testY < 0) { testY = map->height + yVel; }

    if (map->canWalk(testX, testY))
    {
        xPos = testX;
        yPos = testY;
    }
}

void Player::setPosition(int x, int y)
{
    xPos = x;
    yPos = y;
}
