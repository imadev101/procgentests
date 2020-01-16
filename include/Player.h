#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include <bits/stdc++.h>

class Player
{
    public:
        std::string name = "";
        int score = 0;
        int xPos = 0;
        int yPos = 0;
        int xVel = 0; // velocity
        int yVel = 0;
        Player();
        Player(Game *game, Map *map);
        virtual ~Player();

        void render(SDL_Renderer *renderer, int xPosRender, int yPosRender);
        void setPosition(int x, int y);

        void update();
        void move(char direction);


    protected:

    private:

        Game* game;
        Map* map;
};

#endif // PLAYER_H
