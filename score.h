#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

class Score
{
    public:
        Score();
        ~Score();

        void free();
        void incrementScore(){scoreValue++;};
        int getScore() const {return scoreValue;};
        bool createTextTexture(SDL_Renderer*, TTF_Font*, SDL_Color);

    private:
        int scoreValue;
        SDL_Texture* textTexture;
        int imageWidth, imageHeight;

};
