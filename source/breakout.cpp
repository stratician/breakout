// breakout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>



#include <memory>
#include <vector>

#include "Common.h"
#include "Sprite.h"
#include "Player.h"
#include "BulletCtrl.h"
#include "EnemyCtrl.h"

static bool bPlayerWeaponSFXPlaying = false;
static int gSfxFlameDelay = 0;

//The music that will be played
Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;
Mix_Chunk* gFlame = NULL;

SDL_Surface* surf = NULL;


bool bAlive = true;
double PI = 3.14159;
int gLevel = 0;


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

double gGameSpeed = 1.0f;

bool KEY_RIGHT = false;
bool KEY_LEFT = false;
bool KEY_FIRE = false;
bool KEY_FIRE_ALT = false;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close(); 
void CreateLevel(int level);
void playSFX(int type);


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// Textures
SDL_Texture* gTexture = NULL;


// Background Sprite
CSprite* backgroundSpr;
int backgroundTexWidth = 1024;
int backgroundTexHeight = 768;


// Game Objects
Player* player = NULL;

BulletCtrl* bulletCtrl = NULL;
EnemyCtrl* enemyCtrl = NULL;


void Process();
void Render();
void ProcessEnemyEngine();
void RenderStats();


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}

		
		//Initialize SDL_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			return false;
		}
		
	}


	player = new Player();
	player->Init(OWNER_TYPE::OWNER_PLAYER);

	bulletCtrl = new BulletCtrl();
	enemyCtrl = new EnemyCtrl();
	
	

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture(gRenderer, "assets/images/background1.png", backgroundTexWidth, backgroundTexHeight);
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	
	//Load music
	gMusic = Mix_LoadMUS("assets/music/level1.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gScratch = Mix_LoadWAV("assets/sfx/gun-gunshot-01.mp3");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gFlame = Mix_LoadWAV("assets/sfx/flameburst1.wav");
	if (gFlame == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	Mix_ReserveChannels(1);

	
	



	return success;
}

void close()
{
	
	// Remove Player
	if (player)
	{
		delete player;
	}

	if (bulletCtrl)
	{
		delete bulletCtrl;
	}

	if (enemyCtrl)
	{
		delete enemyCtrl;
	}

	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	
	//Free the sound effects
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
		
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();


}



int main(int argc, char* args[])
{

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			backgroundSpr = new CSprite(gTexture, backgroundTexWidth, backgroundTexHeight);

			// Create Level
			CreateLevel(gLevel);

			//Play the music
			
			
			Mix_PlayMusic(gMusic, -1);
			Mix_VolumeMusic(128);
			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							case SDLK_z:
								KEY_LEFT = true;
								break;
							case SDLK_x:
								KEY_RIGHT = true;
								break;
							case  SDLK_m:
								KEY_FIRE = true;
								break;
							case  SDLK_n:
								KEY_FIRE_ALT = true;
								break;
						}
					}
					else if (e.type == SDL_KEYUP)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_z:
							KEY_LEFT = false;
							break;
						case SDLK_x:
							KEY_RIGHT = false;
							break;
						case  SDLK_m:
							KEY_FIRE = false;
							break;
						case  SDLK_n:
							KEY_FIRE_ALT = false;
							break;
						}

						bPlayerWeaponSFXPlaying = false;
						
					}
				}


				Process();

				//Clear screen
				SDL_RenderClear(gRenderer);

				// Render Stuff goes here
				backgroundSpr->Render(gRenderer, 0, 0, 1.0f, 1.0f);

				Render();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void Render()
{
	if (player)
	{
		player->Render();
	}

	if (bulletCtrl)
	{
		bulletCtrl->Render();
	}

	if (enemyCtrl)
	{
		enemyCtrl->Render();
	}
	
	RenderStats();
}



void Process()
{
	
	if (player)
	{
		player->Process();
		player->ProcessInput();
	}

	if (bulletCtrl)
	{
		bulletCtrl->Process();
	}

	if (enemyCtrl)
	{
		
		if(!enemyCtrl->Process() || player->getLife() <= 0)
		{
			if (!bAlive || player->getLife() <= 0)
			{
				gLevel = 0;
				bAlive = true;

				player->Respawn();
			}
			else
			{
				gLevel++;
			}
			
			CreateLevel(gLevel);
		}
	}


	if (gSfxFlameDelay)
	{
		gSfxFlameDelay--;
	}
	else
	{
		if (Mix_Playing(0))
		{
			Mix_HaltChannel(0);
		}
	}

	

}


void CreateLevel(int level)
{
	enemyCtrl->DestroyAll();
	gGameSpeed = 1.0f + ((float)level) * 0.3f;
	
	if (level & 0x1)
	{
		// Boss
		enemyCtrl->Create(1 + level, SCREEN_WIDTH / 2, 100);
	}
	else
	{
		int rows = 1 + ( level >> 1 );
		if (rows > 7)
			rows = 7;

		const int columns = 11;
		for (int j = 0; j < rows; ++j)
		{
			for (int i = 0; i < columns; ++i)
			{
				enemyCtrl->Create(0, 100 + i * ((SCREEN_WIDTH - 200) / columns), 100 + j * 115);
			}
		}
	}
	
}


void RenderStats()
{
	for (int i = 0; i < player->getLife();++i)
	{
		player->getSpr()->Render(gRenderer, i * 35, 0, 0.1f, 0.1f);
	}

}



void playSFX(int type)
{
	switch (type)
	{
		case 0:
			Mix_Volume(-1, 32);
			Mix_PlayChannel(-1, gScratch, 0);
			
		case 1:
			if (bPlayerWeaponSFXPlaying == false)
			{
				bPlayerWeaponSFXPlaying = true;
				gSfxFlameDelay = 60;
				Mix_Volume(-1, 32);
				Mix_PlayChannel(0, gFlame, -1);
				
			}

			break;
	}
}