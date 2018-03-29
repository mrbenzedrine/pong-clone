#include "ball.h"

Ball::Ball(int initPosX, int initPosY, int initVelX, int initVelY, int screen_width, int screen_height)
{

    posX = initPosX;
    posY = initPosY;
    velX = initVelX;
    velY = initVelY;
    ballBox = {posX, posY, BALL_WIDTH, BALL_HEIGHT};
    isBallInPlay = true;

}

void Ball::move(int screen_width, int screen_height, SDL_Rect player1, SDL_Rect player2)
{

    posX += velX;

    if(posX < 0)
    {
        isBallInPlay = false;
    }
    else if(posX > screen_width - BALL_WIDTH)
    {
        isBallInPlay = false;
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

    // Check if the collective movements in this frame have
    // caused a collision with a Paddle
    if(checkCollision(player1, player2))
    {
        posX -= velX;
        posY -= velY;
        velX *= -1;
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

bool Ball::checkCollision(SDL_Rect player1, SDL_Rect player2)
{

    int xAxisProjectionLeftP1, xAxisProjectionLeftP2;
    int xAxisProjectionRightP1, xAxisProjectionRightP2;
    int yAxisProjectionTopP1, yAxisProjectionTopP2;
    int yAxisProjectionBottomP1, yAxisProjectionBottomP2;
    int xAxisProjectionLeftBall, xAxisProjectionRightBall;
    int yAxisProjectionTopBall, yAxisProjectionBottomBall;

    bool hasCollidedWithP1 = true;
    bool hasCollidedWithP2 = true;

    xAxisProjectionLeftP1 = player1.x;
    xAxisProjectionRightP1 = player1.x + player1.w;
    yAxisProjectionTopP1 = player1.y;
    yAxisProjectionBottomP1 = player1.y + player1.h;

    xAxisProjectionLeftP2 = player2.x;
    xAxisProjectionRightP2 = player2.x + player2.w;
    yAxisProjectionTopP2 = player2.y;
    yAxisProjectionBottomP2 = player2.y + player2.h;

    xAxisProjectionLeftBall = posX;
    xAxisProjectionRightBall = posX + BALL_WIDTH;
    yAxisProjectionTopBall = posY;
    yAxisProjectionBottomBall = posY +BALL_HEIGHT;

    // Check if the projections of either Paddle overlaps with
    // the projections of the Ball

    if(xAxisProjectionRightP1 <= xAxisProjectionLeftBall)
    {
        hasCollidedWithP1 = false;
    }

    if(xAxisProjectionLeftP1 >= xAxisProjectionRightBall)
    {
        hasCollidedWithP1 = false;
    }

    if(yAxisProjectionTopP1 >= yAxisProjectionBottomBall)
    {
        hasCollidedWithP1 = false;
    }

    if(yAxisProjectionBottomP1 <= yAxisProjectionTopBall)
    {
        hasCollidedWithP1 = false;
    }

    if(xAxisProjectionRightP2 <= xAxisProjectionLeftBall)
    {
        hasCollidedWithP2 = false;
    }

    if(xAxisProjectionLeftP2 >= xAxisProjectionRightBall)
    {
        hasCollidedWithP2 = false;
    }

    if(yAxisProjectionTopP2 >= yAxisProjectionBottomBall)
    {
        hasCollidedWithP2 = false;
    }

    if(yAxisProjectionBottomP2 <= yAxisProjectionTopBall)
    {
        hasCollidedWithP2 = false;
    }

    return hasCollidedWithP1 || hasCollidedWithP2;

}

void Ball::reset(int screen_width, int screen_height)
{

    int starting_height = screen_height/2;
    int init_x_vel = 1;
    int init_y_vel = 1;

    posX = screen_width/2;
    posY = starting_height;

    velX = init_x_vel;
    velY = init_y_vel;

    isBallInPlay = true;

}
