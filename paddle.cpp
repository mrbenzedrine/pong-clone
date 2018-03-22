/* This piece of code was originally from Lazy Foo' Productions,
and has been used as the foundation to which changes and additions
have been made to create the code below
(http://lazyfoo.net/) */

#include "paddle.h"

Paddle::Paddle(int x, SDL_Keycode up, SDL_Keycode down, int screen_height)
{
    velY = 0;

    up_key = up;
    down_key = down;

    posX = x;
    posY = screen_height/2 - PADDLE_HEIGHT/2;

}

void Paddle::handleEvent(SDL_Event& e)
{

    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {

        if(e.key.keysym.sym == up_key)
        {
            velY -= PADDLE_VEL;
        }
        else if(e.key.keysym.sym == down_key)
        {
            velY += PADDLE_VEL;
        }

    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {

        if(e.key.keysym.sym == up_key)
        {
            velY += PADDLE_VEL;
        }
        else if(e.key.keysym.sym == down_key)
        {
            velY -= PADDLE_VEL;
        }

    }

}

void Paddle:: move(int screen_height)
{

    posY += velY;

    if(posY < 0 || posY + PADDLE_HEIGHT > screen_height)
    {
        posY -= velY;
    }

}

void Paddle::render(SDL_Renderer* renderer)
{

    SDL_Rect paddle = {posX, posY, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &paddle);

}
