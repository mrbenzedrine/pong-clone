/* This piece of code was originally from Lazy Foo' Productions,
and has been used as the foundation to which changes and additions
have been made to create the code below
(http://lazyfoo.net/) */

#include <SDL2/SDL.h>

class Paddle
{
    public:
        static const int PADDLE_HEIGHT = 30;
        static const int PADDLE_WIDTH = 8;
        static const int PADDLE_VEL = 1;

        Paddle(int x, SDL_Keycode up, SDL_Keycode down, int screen_height);

        void handleEvent(SDL_Event& e);
        void move(int screen_height);
        void render(SDL_Renderer* renderer);

    private:
        int posX, posY;
        int velY;

        SDL_Rect paddleBox;
        SDL_Keycode up_key, down_key;

};
