/* This piece of code was originally from Lazy Foo' Productions,
and has been used as the foundation to which changes and additions
have been made to create the code below
(http://lazyfoo.net/) */

#include <stdio.h>
#include <SDL2/SDL.h>

#include "paddle.h"
#include "ball.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();
bool loadMedia();
void drawCentreLine();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			}
		}
	}

	return success;
}

void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
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

			//Event handler
			SDL_Event e;

            Paddle player1(10, SDLK_w, SDLK_s, SCREEN_HEIGHT);
            Paddle player2(SCREEN_WIDTH - 10 - Paddle::PADDLE_WIDTH, SDLK_UP, SDLK_DOWN, SCREEN_HEIGHT);

            Ball ball(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            bool hasPointBeenWon = false;
            bool hasBreakTimerStarted = false;
            Uint32 timeOfPointWin;
            int player1Score = 0;
            int player2Score = 0;

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

                if(ball.getPosX() < SCREEN_WIDTH/2)
                {
                    ball.move(SCREEN_WIDTH, SCREEN_HEIGHT, player1.getCollisionBox());
                }
                else
                {
                    ball.move(SCREEN_WIDTH, SCREEN_HEIGHT, player2.getCollisionBox());
                }

                if(!ball.isBallInPlay && !hasBreakTimerStarted)
                {
                    hasPointBeenWon = true;

                    if(ball.getPosX() < 0)
                    {
                        player1Score++;
                    }
                    else
                    {
                        player2Score++;
                    }
                    printf("player1Score is: %d\nplayer2Score is: %d\n", player1Score, player2Score);
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( gRenderer );

                drawCentreLine();

                player1.render(gRenderer);
                player2.render(gRenderer);

                if(!hasPointBeenWon)
                {
                    ball.render(gRenderer);
                }
                else
                {
                    if(!hasBreakTimerStarted)
                    {
                        // Get start time of the break between points
                        timeOfPointWin = SDL_GetTicks();
                        hasBreakTimerStarted = true;
                    }
                }

                //Update screen
                SDL_RenderPresent( gRenderer );

                if(hasBreakTimerStarted && (SDL_GetTicks() - timeOfPointWin > 2000))
                {
                    if(ball.getPosX() < 0)
                    {
                        ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, -1);
                    }
                    else
                    {
                        ball.reset(SCREEN_WIDTH, SCREEN_HEIGHT, 1);
                    }

                    // Reset hasPointBeenWon and hasBreakTimerStarted
                    hasPointBeenWon = false;
                    hasBreakTimerStarted = false;
                }
			}
		}
	}

	close();

	return 0;
}
