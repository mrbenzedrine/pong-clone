#include <SDL2/SDL.h>
#include <cmath>

class Ball
{

    public:
        static const int BALL_WIDTH = 6;
        static const int BALL_HEIGHT = 6;

        bool isBallInPlay;

        Ball(float initPosX, float initPosY, float initVelX, float initVelY, int screen_width, int screen_height);

        void move(int screen_width, int screen_height, SDL_Rect player);
        void render(SDL_Renderer* renderer);
        bool checkCollision(SDL_Rect player);
        void reset(int screen_width, int screen_height, int x_vel_sign_multiplier);
        void calculateVelocityAfterPaddleCollision(int screen_width, SDL_Rect);
        float getPosX() const {return posX;};

    private:
        float posX, posY;
        float velX, velY;
        SDL_Rect ballBox;

};
