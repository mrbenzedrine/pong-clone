#include "ball.h"

Ball::Ball(int initPosX, int initPosY, int initVelX, int initVelY, int screen_width, int screen_height)
{

    posX = initPosX;
    posY = initPosY;
    velX = initVelX;
    velY = initVelY;

}

void Ball::render(SDL_Renderer* renderer)
{

    SDL_Rect ball = {posX, posY, BALL_WIDTH, BALL_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &ball);

}
