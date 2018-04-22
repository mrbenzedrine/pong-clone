#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

template <class T> class TextTexture
{
    public:
        TextTexture(T);
        ~TextTexture(){free();};

        void free();
        bool createTextTexture(SDL_Renderer*, TTF_Font*, SDL_Color);
        void render(int, int, SDL_Renderer*);
        int getImageWidth() const {return imageWidth;};

    private:
        int imageWidth, imageHeight;
        T valueToRender;
        SDL_Texture* textTexture;
};

template <class T>
TextTexture<T>::TextTexture(T value)
{
    imageWidth = 0;
    imageHeight = 0;
    valueToRender = value;
    textTexture = NULL;
}

template <class T>
void TextTexture<T>::free()
{

    if(textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
        imageWidth = 0;
        imageHeight = 0;
    }

}

template <class T>
bool TextTexture<T>::createTextTexture(SDL_Renderer* renderer, TTF_Font* textFont, SDL_Color textColour)
{

    free();

    std::stringstream textStream;

    textStream.str("");
    textStream << valueToRender;

    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, textStream.str().c_str(), textColour);

    if(textSurface == NULL)
    {
        printf("Unable to create text surface. SDL_ttf error: %s\n", TTF_GetError());
    }
    else
    {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if(textTexture == NULL)
        {
            printf("Unable to create text texture. SDL error: %s\n", SDL_GetError());
        }
        else
        {
            imageWidth = textSurface->w;
            imageHeight = textSurface->h;
        }
    }

    SDL_FreeSurface(textSurface);

    return textTexture != NULL;

}

template <class T>
void TextTexture<T>::render(int x, int y, SDL_Renderer* renderer)
{

    SDL_Rect windowRenderArea = {x, y, imageWidth, imageHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &windowRenderArea);

}
