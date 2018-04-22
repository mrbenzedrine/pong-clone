#include "text_texture.h"

TextTexture::TextTexture(std::string text)
{
    imageWidth = 0;
    imageHeight = 0;
    textToRender = text;
    textTexture = NULL;
}

TextTexture::~TextTexture()
{

    free();

}

void TextTexture::free()
{

    if(textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
        imageWidth = 0;
        imageHeight = 0;
        textToRender = "";
    }

}

bool TextTexture::createTextTexture(SDL_Renderer* renderer, TTF_Font* textFont, SDL_Color textColour)
{

    free();

    std::stringstream textStream;

    textStream.str("");
    textStream << textToRender;

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

void TextTexture::render(int x, int y, SDL_Renderer* renderer)
{

    SDL_Rect windowRenderArea = {x, y, imageWidth, imageHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &windowRenderArea);

}
