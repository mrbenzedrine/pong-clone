#include "ball.h"

Ball::Ball(float initPosX, float initPosY, float initVelX, float initVelY, int screen_width, int screen_height, Mix_Chunk* paddle_collision_fx, Mix_Chunk* wall_collision_fx)
{

    posX = initPosX;
    posY = initPosY;
    velX = initVelX;
    velY = initVelY;
    ballBox = {posX, posY, BALL_WIDTH, BALL_HEIGHT};
    isBallInPlay = true;
    paddleCollisionFX = paddle_collision_fx;
    wallCollisionFX = wall_collision_fx;

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
        Mix_PlayChannel(-1, wallCollisionFX, 0);

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
        Mix_PlayChannel(-1, paddleCollisionFX, 0);

        posX -= velX;
        posY -= velY;

        calculateVelocityAfterPaddleCollision(screen_width, player);
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
    float xAxisProjectionLeftBall, xAxisProjectionRightBall;
    float yAxisProjectionTopBall, yAxisProjectionBottomBall;

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

void Ball::reset(int screen_width, int screen_height, int x_vel_sign_multiplier)
{

    int starting_height = screen_height/2;
    float init_x_vel = 1;
    float init_y_vel = 1;

    posX = screen_width/2;
    posY = starting_height;

    velX = init_x_vel * x_vel_sign_multiplier;
    velY = init_y_vel;

    isBallInPlay = true;

}

void Ball::calculateVelocityAfterPaddleCollision(int screen_width, SDL_Rect player)
{

    float collision_y_coord;
    float bounce_angle;

    // Get the y coord of the point on the Paddle where
    // the Ball collided with it

    collision_y_coord = posY - player.y;

    // Start with a simple formula for the bounce angle:
    // at the centre of the Paddle the bounce angle will be
    // 90 degress relative to the Paddle, and for every
    // pixel up/down from the centre the angle will
    // decrease by 4 degrees

    if(collision_y_coord < player.h/2)
    {
        bounce_angle = (M_PI/180) * (90 - 4 * (player.h/2 - collision_y_coord));

        // Sign of y velocity will be negative
        velY = -cos(bounce_angle);

    }
    else
    {
        bounce_angle = (M_PI/180) * (90 - 4 * (collision_y_coord - player.h/2));

        // Sign of y velocity will be positive
        velY = cos(bounce_angle);
    }

    if(posX < screen_width/2)
    {
        // x velocity should be positive after collision
        velX = sin(bounce_angle);
    }
    else
    {
        // x velocity should be negative after collision
        velX = -sin(bounce_angle);
    }

}
