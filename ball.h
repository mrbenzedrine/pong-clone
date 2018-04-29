/* This piece of code was originally from Lazy Foo' Productions,
and has been used as the foundation to which changes and additions
have been made to create the code below
(http://lazyfoo.net/) */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <stdexcept>

class Ball
{

    public:
        static const int BALL_WIDTH = 6;
        static const int BALL_HEIGHT = 6;

        Ball(int screen_width, int screen_height, Mix_Chunk* paddle_collision_fx, Mix_Chunk* wall_collision_fx);

        void introMove(int screen_width, int screen_height);
        void move(int screen_width, int screen_height, SDL_Rect player);
        void render(SDL_Renderer* renderer);
        void reset(int screen_width, int screen_height, int x_vel_sign_multiplier);
        float getPosX() const {return posX;};
        bool getIsInPlay() const {return isInPlay;};
        void setIsInPlay(bool value){isInPlay = value;};

    private:
        static const int ANGLE_LOWER_BOUND = 45;
        static const int ANGLE_UPPER_BOUND = 135;
        static const int Y_POS_RESET_CUTOFF = 40;

        float posX, posY;
        float velX, velY;
        bool isInPlay;
        SDL_Rect ballBox;
        Mix_Chunk* paddleCollisionFX;
        Mix_Chunk* wallCollisionFX;
        Uint32 timeOfCollision;

        bool checkCollision(SDL_Rect player);
        void calculateVelocityAfterPaddleCollision(int screen_width, SDL_Rect);

};

int nrand(int, int);
