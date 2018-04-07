#include "score.h"

Score::Score()
{

    scoreValue = 0;
    textTexture = NULL;
    imageWidth = 0;
    imageHeight = 0;

}

Score::~Score()
{

    free();

}

void Score::free()
{

    if(textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
        scoreValue = 0;
        imageWidth = 0;
        imageHeight = 0;
    }

}

bool Score::createTextTexture(SDL_Renderer* renderer, TTF_Font* textFont, SDL_Color textColour)
{

    // Get rid of the old texture
    free();

    std::stringstream scoreText;

    // Set the text to be rendered
    scoreText.str("");
    scoreText << scoreValue;

    // Create SDL_Surface which will in turn be used
    // to create an SDL_Texture
    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, scoreText.str().c_str(), textColour);

    if(textSurface == NULL)
    {
        printf("Unable to create text surface. SDL_ttf error: %s\n", TTF_GetError());
    }
    else
    {
        // Create SDL_Texture from SDL_Surface
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
