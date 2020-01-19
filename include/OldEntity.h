#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"
#include <bits/stdc++.h>

class OldEntity
{
    public:
        static int static_id;

        int id;

        int xPos = 0;
        int yPos = 0;
        int xVel = 0; // velocity
        int yVel = 0;
        int mana = 1000;
        int pxSize = 30;

        OldEntity* children[10] = {NULL};
        int nbChildren = 0;
        int depth = 0;

        OldEntity();
        //Entity(Game *game);
        virtual ~OldEntity();

        void render(SDL_Renderer *renderer);
        void setPosition(int x, int y);

        void init();
        void update();
        void move();

        void sprout();
        void spawn();


    protected:

    private:

        //Game* game;
};

#endif // ENTITY_H
