#include "score.h"

Score::Score()
{

    scoreValue = 0;
    textTexture = NULL;

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
    }

}
