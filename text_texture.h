#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

class TextTexture
{
    public:
        TextTexture(std::string);
        ~TextTexture();

        void free();
        bool createTextTexture(SDL_Renderer*, TTF_Font*, SDL_Color);
        void render(int, int, SDL_Renderer*);
        int getImageWidth() const {return imageWidth;};

    private:
        int imageWidth, imageHeight;
        std::string textToRender;
        SDL_Texture* textTexture;
};
