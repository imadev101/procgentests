#include "Entity.h"
#include<stdlib.h>
#include<time.h>

//SDL_Texture *texture = NULL;

// config

const int SPROUT_CHANCE = 20; // 20% each frame
const int SPEED_FACTOR = 6; // -6 to +6 vector in x and y

int Entity::static_id = 0;

Entity::Entity()
{
    //ctor
    id = ++static_id;

    srand(SDL_GetTicks()+static_id*10);

    xPos = rand() % Game::MAP_WIDTH;
    yPos = rand() % Game::MAP_HEIGHT;
    xVel = rand() % (2*SPEED_FACTOR) - SPEED_FACTOR;
    yVel = rand() % (2*SPEED_FACTOR) - SPEED_FACTOR;
}

Entity::~Entity()
{
    //dtor
}

void Entity::init()
{
    // random spawn
    // random position
    // random velocity
    // random direction
}

void Entity::move()
{
    // using modulo allow to round up around map
    int testX = (xPos+xVel)%Game::MAP_WIDTH;
    if (testX < 0) { testX = Game::MAP_WIDTH + xVel; }
    int testY = (yPos+yVel)%Game::MAP_HEIGHT;
    if (testY < 0) { testY = Game::MAP_HEIGHT + yVel; }

    /*if ((testX>0)&&(testX<Game::MAP_WIDTH)&&(testY>0)&&(testY<Game::MAP_HEIGHT))
    {
        xPos = testX;
        yPos = testY;
    }*/
    xPos = testX;
    yPos = testY;
}

void Entity::render(SDL_Renderer *renderer)
{
    int multiplier = 1;
    SDL_Rect eRect;
    eRect.x = xPos;
    eRect.y = yPos;
    eRect.w = (pxSize+2)*multiplier;
    eRect.h = (pxSize+2)*multiplier;

    SDL_SetRenderDrawColor(renderer, 255-(nbChildren*25), nbChildren*25, yPos%255, 0xFF);

    SDL_RenderFillRect(renderer, &eRect);

    for (int i = 0; i < nbChildren; i++)
    {
        if (children[i]->pxSize > 0)
        {
            children[i]->render(renderer);
        }
    }

}

void Entity::update()
{
    srand(SDL_GetTicks()+static_id*100);
    //std::cout << "2 Seeding srand with  SDLGT = " << SDL_GetTicks() << std::endl;

    move();


    int sproutChance = 100 - SPROUT_CHANCE;
    int willSprout = rand() % 100;

    if ((mana>0)&&(pxSize>1)&&(sproutChance<willSprout)&&(depth<20)&&(nbChildren<10))
    {
        //std::cout << "Sprouting at depth " << depth << std::endl;
        sprout();
    }

    for (int i = 0; i < nbChildren; i++)
    {
        if (children[i]->pxSize > 0)
        {
            children[i]->update();
        }
    }
}

void Entity::sprout()
{
    // some checks here?
    spawn();
}

void Entity::spawn()
{
    int manaCost = rand() % 50;

    if (mana < 5)
    {
        mana = 0;
    // not enough mana but kills unit
    }
    else
    {
        int number = rand() % 2 + 1;

       // std::cout << "Spawning " << number << " entities..." << std::endl;
        for (int i = 0; i < number; i++)
        {
            Entity* e = new Entity();
            e->init();

            e->id = id + nbChildren + 10*depth;

            e->depth = depth + 1;
            double manaTemp = (mana / number);
            e->mana =  (int)manaTemp - 5;

            e->setPosition(xPos, yPos);

            double pxsTemp = (pxSize / number);
            e->pxSize = (int)pxsTemp;

            /*std::cout << "Entity #" << i << ": x=" << e->xPos << " / y=" << e->yPos
            << " / xV=" << e->xVel << " / yV=" << e->yVel << std::endl;*/

            pxSize--;

            children[nbChildren] = e;
            nbChildren++;

            if (nbChildren>9)
            {
                break;
            }
        }
        mana -= manaCost;
    }
}
void Entity::setPosition(int x, int y)
{
    xPos = x;
    yPos = y;
}
