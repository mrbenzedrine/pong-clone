#include "ball.h"

Ball::Ball(int screen_width, int screen_height, Mix_Chunk* paddle_collision_fx, Mix_Chunk* wall_collision_fx)
{

    reset(screen_width, screen_height, -1);

    ballBox = {posX, posY, BALL_WIDTH, BALL_HEIGHT};
    paddleCollisionFX = paddle_collision_fx;
    wallCollisionFX = wall_collision_fx;
    timeOfCollision = 0;

}

void Ball::move(int screen_width, int screen_height, SDL_Rect player)
{

    posX += velX;

    if(posX < 0)
    {
        isInPlay = false;
    }
    else if(posX > screen_width - BALL_WIDTH)
    {
        isInPlay = false;
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
    if(checkCollision(player) && (SDL_GetTicks() - timeOfCollision > 1000))
    {
        timeOfCollision = SDL_GetTicks();

        Mix_PlayChannel(-1, paddleCollisionFX, 0);

        posX -= velX;
        posY -= velY;

        calculateVelocityAfterPaddleCollision(screen_width, player);

        posX += velX;
        posY += velY;
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

    int starting_height = nrand(Y_POS_RESET_CUTOFF, screen_height - Y_POS_RESET_CUTOFF);

    float ball_angle = nrand(ANGLE_LOWER_BOUND, ANGLE_UPPER_BOUND + 1) * (M_PI/180);
    float init_x_vel = sin(ball_angle);
    float init_y_vel = cos(ball_angle);

    posX = screen_width/2;
    posY = starting_height;

    velX = init_x_vel * x_vel_sign_multiplier;
    velY = init_y_vel;

    isInPlay = true;

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
    // decrease by angle_step degrees

    const int angle_step = 4;

    if(collision_y_coord < player.h/2)
    {
        if(collision_y_coord < 0)
        {
            collision_y_coord = 0.0;
        }

        bounce_angle = (M_PI/180) * (90 - angle_step * (player.h/2 - collision_y_coord));

        // Sign of y velocity will be negative
        velY = -cos(bounce_angle);

    }
    else
    {
        if(collision_y_coord > player.h)
        {
            collision_y_coord = player.h;
        }

        bounce_angle = (M_PI/180) * (90 - angle_step * (collision_y_coord - player.h/2));

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

// Generates a pseudo-random integer in the interval [m, n)
int nrand(int m, int n)
{

    if(m <= 0 || n > RAND_MAX)
    {
        throw std::domain_error("Arguments(s) of nrand are out of range");
    }

    const int bucket_size = RAND_MAX / (n-m);
    int r;

    do r = rand() / bucket_size;
    while (r >= (n-m));

    return r + m;

}
