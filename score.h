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
        void render(int, int, SDL_Renderer*);
        int getImageWidth() const {return imageWidth;};

    private:
        int scoreValue;
        SDL_Texture* textTexture;
        int imageWidth, imageHeight;

};
