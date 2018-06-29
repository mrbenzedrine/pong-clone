/* This piece of code was originally from Lazy Foo' Productions,
and has been used as the foundation to which changes and additions
have been made to create the code below
(http://lazyfoo.net/) */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ctime>

#include "paddle.h"
#include "ball.h"
#include "text_texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCORE_DISPLAY_X_OFFSET = 20;
const int SCORE_DISPLAY_Y_OFFSET = 20;
const int PADDLE_X_OFFSET = 10;

bool init();
void close();
bool loadMedia();
void drawCentreLine();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* font = NULL;
TextTexture<int> player1ScoreTexture(0), player2ScoreTexture(0);
std::string fontAcknowledgementText = "Font used is 'Lazy Font' and is copyrighted by Lazy Foo' Productions";
TextTexture<std::string> fontAcknowledgementTextTexture(fontAcknowledgementText);
Mix_Chunk* winPointFX = NULL;
Mix_Chunk* paddleCollisionFX = NULL;
Mix_Chunk* wallCollisionFX = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                // Initialise SDL_ttf

                if(TTF_Init() == -1)
                {
                    printf("Unable to initialise SDL_ttf, SDL_ttf error: %s\n", TTF_GetError());
                    success = false;
                }

                // Initialise SDL_mixer

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("Unable to initialise SDL_mixer, SDL_mixer error: %s\n", Mix_GetError());
                    success = false;
                }

			}
		}
	}

	return success;
}

void close()
{
    Mix_FreeChunk(winPointFX);
    Mix_FreeChunk(paddleCollisionFX);
    Mix_FreeChunk(wallCollisionFX);
    winPointFX = NULL;
    paddleCollisionFX = NULL;
    wallCollisionFX = NULL;

    player1ScoreTexture.free();
    player2ScoreTexture.free();

    TTF_CloseFont(font);
    font = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

    Mix_Quit();
    TTF_Quit();
	SDL_Quit();
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

    font = TTF_OpenFont("lazy.ttf", 16);

    if(font == NULL)
    {
        printf("Failed to load font! SDL_ttf error: %s\n", TTF_GetError());
        success = false;
    }

    winPointFX = Mix_LoadWAV("win_point.wav");
    if(winPointFX == NULL)
    {
        printf("Unable to load win point sound effect, SDL_mixer error: %s\n", Mix_GetError());
    }

    paddleCollisionFX = Mix_LoadWAV("paddle_collision.wav");
    if(paddleCollisionFX == NULL)
    {
        printf("Unable to load paddle collision sound effect, SDL_mixer error: %s\n", Mix_GetError());
    }

    wallCollisionFX = Mix_LoadWAV("wall_collision.wav");
    if(wallCollisionFX == NULL)
    {
        printf("Unable to load wall collision sound effect, SDL_mixer error: %s\n", Mix_GetError());
    }

	return success;
}

void drawCentreLine()
{

    int line_height = 7;
    int line_width = 2;
    int gap_between_lines = 4;
    SDL_Rect centreLine = {SCREEN_WIDTH / 2, 0, line_width, line_height};

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for(int line_counter = 0; line_counter * (line_height + gap_between_lines) <  SCREEN_HEIGHT; line_counter++)
    {
        centreLine.y = line_counter * (line_height + gap_between_lines);
        SDL_RenderFillRect(gRenderer, &centreLine);
    }

}

int main()
{
    srand(time(NULL));

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;
            bool exit_intro = false;

			//Event handler
			SDL_Event e;

            Ball ball(SCREEN_WIDTH, SCREEN_HEIGHT, paddleCollisionFX, wallCollisionFX);
            int player1Score = 0;
            int player2Score = 0;

            std::string introScreenText = "Press enter to begin";
            TextTexture<std::string> introScreenTextTexture(introScreenText);
            SDL_Color textColour = {255, 255, 255};

            introScreenTextTexture.createTextTexture(gRenderer, font, textColour);
            fontAcknowledgementTextTexture.createTextTexture(gRenderer, font, textColour);

            // Intro screen
            while(!quit && !exit_intro)
            {
                while(SDL_PollEvent(&e) != 0)
                {

                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                    // Check if the user has pressed the enter key to start
                    // the game
                    if(currentKeyStates[SDL_SCANCODE_RETURN])
                    {
                        exit_intro = true;
                    }
                }


                ball.introMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(gRenderer);

                introScreenTextTexture.render(SCREEN_WIDTH/2 - introScreenTextTexture.getImageWidth()/2, SCREEN_HEIGHT/2, gRenderer);
                fontAcknowledgementTextTexture.render(SCREEN_WIDTH/2 - fontAcknowledgementTextTexture.getImageWidth()/2, SCORE_DISPLAY_Y_OFFSET, gRenderer);

                drawCentreLine();

                ball.render(gRenderer);

                if(!player1ScoreTexture.createTextTexture(gRenderer, font, textColour) || !player2ScoreTexture.createTextTexture(gRenderer, font, textColour))
                {
                    printf("Unable to render player score");
                }

                player1ScoreTexture.render(SCORE_DISPLAY_X_OFFSET, SCORE_DISPLAY_Y_OFFSET, gRenderer);
                player2ScoreTexture.render(SCREEN_WIDTH - SCORE_DISPLAY_X_OFFSET - player2ScoreTexture.getImageWidth(), SCORE_DISPLAY_Y_OFFSET, gRenderer);

                SDL_RenderPresent(gRenderer);

            }

            Paddle player1(PADDLE_X_OFFSET, SDLK_w, SDLK_s, SCREEN_HEIGHT);
            Paddle player2(SCREEN_WIDTH - PADDLE_X_OFFSET - Paddle::PADDLE_WIDTH, SDLK_UP, SDLK_DOWN, SCREEN_HEIGHT);

            bool hasBreakTimerStarted = true;
            Uint32 timeOfPointWin = SDL_GetTicks();
            ball.setIsInPlay(false);

			//While application is running
			while( !quit )
			{

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    player1.handleEvent(e);
                    player2.handleEvent(e);

                }

                player1.move(SCREEN_HEIGHT);
                player2.move(SCREEN_HEIGHT);

                if(ball.getIsInPlay())
                {
                    if(ball.getPosX() < SCREEN_WIDTH/2)
                    {
                        ball.move(SCREEN_WIDTH, SCREEN_HEIGHT, player1.getCollisionBox());
                    }
                    else
                    {
                        ball.move(SCREEN_WIDTH, SCREEN_HEIGHT, player2.getCollisionBox());
                    }

                }

                if(!ball.getIsInPlay() && !hasBreakTimerStarted)
                {
                    Mix_PlayChannel(-1, winPointFX, 0);

                    if(ball.getPosX() < 0)
                    {
                        ++player2Score;
                        player2ScoreTexture.setValueToRender(player2Score);
                        if(!player2ScoreTexture.createTextTexture(gRenderer, font, textColour))
                        {
                            printf("Unable to render player2 score");
                        }
                    }
                    else
                    {
                        ++player1Score;
                        player1ScoreTexture.setValueToRender(player1Score);
                        if(!player1ScoreTexture.createTextTexture(gRenderer, font, textColour))
                        {
                            printf("Unable to render player1 score");
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( gRenderer );

                drawCentreLine();

                player1.render(gRenderer);
                player2.render(gRenderer);

                if(ball.getIsInPlay())
                {
                    ball.render(gRenderer);
                }
                else if(!ball.getIsInPlay() && !hasBreakTimerStarted)
                {
                    // Get start time of the break between points
                    timeOfPointWin = SDL_GetTicks();
                    hasBreakTimerStarted = true;
                }

                player1ScoreTexture.render(SCORE_DISPLAY_X_OFFSET, SCORE_DISPLAY_Y_OFFSET, gRenderer);
                player2ScoreTexture.render(SCREEN_WIDTH - SCORE_DISPLAY_X_OFFSET - player2ScoreTexture.getImageWidth(), SCORE_DISPLAY_Y_OFFSET, gRenderer);

                //Update screen
                SDL_RenderPresent( gRenderer );

                if(hasBreakTimerStarted && (SDL_GetTicks() - timeOfPointWin > 2000))
                {
                    if(ball.getPosX() < 0)
                    {
                        ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, -1);
                    }
                    else if(ball.getPosX() > SCREEN_WIDTH - Ball::BALL_WIDTH)
                    {
                        ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, 1);
                    }
                    else
                    {
                        // Then the user has just exited out of the intro screen
                        // and the game has only begun, so the Ball should go
                        // towards player 1
                        ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, -1);
                    }

                    // Reset hasBreakTimerStarted
                    hasBreakTimerStarted = false;
                }

			}
		}
	}

	close();

	return 0;
}
