#include <SDL2/SDL.h>

class Ball
{

    public:
        static const int BALL_WIDTH = 6;
        static const int BALL_HEIGHT = 6;

        Ball(int initPosX, int initPosY, int initVelX, int initVelY, int screen_width, int screen_height);

        void move(int screen_width, int screen_height);
        void render(SDL_Renderer* renderer);

    private:
        int posX, posY;
        int velX, velY;

};
