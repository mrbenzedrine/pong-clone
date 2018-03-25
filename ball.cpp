#include "ball.h"

Ball::Ball(int initPosX, int initPosY, int initVelX, int initVelY, int screen_width, int screen_height)
{

    posX = initPosX;
    posY = initPosY;
    velX = initVelX;
    velY = initVelY;
    ballBox = {posX, posY, BALL_WIDTH, BALL_HEIGHT};

}

void Ball::move(int screen_width, int screen_height)
{

    posX += velX;

    if(posX < 0)
    {
        // player2 scores a point
    }
    else if(posX > screen_width - BALL_WIDTH)
    {
        // player1 scores a point
    }

    posY += velY;

    if(posY < 0 || posY > screen_height - BALL_HEIGHT)
    {
        // Move the ball back, and reverse the sign of the
        // y velocity component to make the ball 'bounce'
        // off the bottom/top of the window

        posY -= velY;
        velY *= -1;
    }

    // Update ballBox
    ballBox.x = posX;
    ballBox.y = posY;

}

void Ball::render(SDL_Renderer* renderer)
{

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &ballBox);

}
