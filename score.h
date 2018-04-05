#include <SDL2/SDL.h>

class Score
{
    public:
        Score();
        ~Score();

        void free();
        void incrementScore(){scoreValue++;};
        int getScore() const {return scoreValue;};

    private:
        int scoreValue;
        SDL_Texture* textTexture;

};
