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

void Ball::move(int screen_width, int screen_height, SDL_Rect player)
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
    // caused a collision with the Paddle in the same half
    // of the screen as the Ball
    if(checkCollision(player))
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

bool Ball::checkCollision(SDL_Rect player)
{

    int xAxisProjectionLeftPlayer, xAxisProjectionRightPlayer;
    int yAxisProjectionTopPlayer, yAxisProjectionBottomPlayer;
    int xAxisProjectionLeftBall, xAxisProjectionRightBall;
    int yAxisProjectionTopBall, yAxisProjectionBottomBall;

    xAxisProjectionLeftPlayer = player.x;
    xAxisProjectionRightPlayer = player.x + player.w;
    yAxisProjectionTopPlayer = player.y;
    yAxisProjectionBottomPlayer = player.y + player.h;

    xAxisProjectionLeftBall = posX;
    xAxisProjectionRightBall = posX + BALL_WIDTH;
    yAxisProjectionTopBall = posY;
    yAxisProjectionBottomBall = posY +BALL_HEIGHT;

    // Check if the projections of the player's Paddle overlaps with
    // the projections of the Ball

    if(xAxisProjectionRightPlayer <= xAxisProjectionLeftBall)
    {
        return false;
    }
    else if(xAxisProjectionLeftPlayer >= xAxisProjectionRightBall)
    {
        return false;
    }
    else if(yAxisProjectionTopPlayer >= yAxisProjectionBottomBall)
    {
        return false;
    }
    else if(yAxisProjectionBottomPlayer <= yAxisProjectionTopBall)
    {
        return false;
    }

    return true;

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
