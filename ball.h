#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <stdexcept>

class Ball
{

    public:
        static const int BALL_WIDTH = 6;
        static const int BALL_HEIGHT = 6;
        static const int ANGLE_LOWER_BOUND = 45;
        static const int ANGLE_UPPER_BOUND = 135;
        static const int Y_POS_RESET_CUTOFF = 40;

        Ball(int screen_width, int screen_height, Mix_Chunk* paddle_collision_fx, Mix_Chunk* wall_collision_fx);

        void move(int screen_width, int screen_height, SDL_Rect player);
        void render(SDL_Renderer* renderer);
        bool checkCollision(SDL_Rect player);
        void reset(int screen_width, int screen_height, int x_vel_sign_multiplier);
        void calculateVelocityAfterPaddleCollision(int screen_width, SDL_Rect);
        float getPosX() const {return posX;};
        bool getIsInPlay() const {return isInPlay;};

    private:
        float posX, posY;
        float velX, velY;
        bool isInPlay;
        SDL_Rect ballBox;
        Mix_Chunk* paddleCollisionFX;
        Mix_Chunk* wallCollisionFX;
        Uint32 timeOfCollision;

};

int nrand(int, int);
