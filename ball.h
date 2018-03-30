#include <SDL2/SDL.h>

class Ball
{

    public:
        static const int BALL_WIDTH = 6;
        static const int BALL_HEIGHT = 6;

        bool isBallInPlay;

        Ball(int initPosX, int initPosY, int initVelX, int initVelY, int screen_width, int screen_height);

        void move(int screen_width, int screen_height, SDL_Rect player);
        void render(SDL_Renderer* renderer);
        bool checkCollision(SDL_Rect player);
        void reset(int screen_width, int screen_height);
        int getPosX() const {return posX;};

    private:
        int posX, posY;
        int velX, velY;
        SDL_Rect ballBox;

};
