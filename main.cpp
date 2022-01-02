

#include "LTexture.h"
#include "Animation.h"
#include "LButton.h"

#include "GameObject.h"
#include "Boid.h"
#include "Global.h"


//Starts up SDL and creates window
bool init();

/// <summary>
/// Loads Image on a texture pointer
/// </summary>
/// <param name="path">Path to file + name</param>
/// <returns>Texture pointer to the created texture</returns>
SDL_Texture* LoadMediaOnTexture(const char* path);

bool LoadMedia();

void LoadBoids();

//Load suface
//SDL_Surface* loadSurface(const char* path);

//Frees media and shuts down SDL
void Close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
//SDL_Surface* gScreenSurface = NULL;

SDL_Texture* loadTexture(const char* path);

SDL_Renderer* gRenderer = NULL;



void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height);

void DrawFilledRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);

void SetBackgroundColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void CreateViewPort(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height);


LTexture arrowTexture;

LTexture backgroundTexture;

// Texture to store in memory
LTexture spriteSheetTexture;
// Sprites the input texture has
SDL_Rect spriteClips[4];

// Color modulation components
Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;

// Alpha modulation components
Uint8 a = 255;

// Walking Animation
Animation characterAnim;


// Font Texture
LTexture textTexture;


LButton topLeftButton;


// Boid Objects

Boid tempBoids[NOOFBOIDS];
GameObject tempBoidObjects[NOOFBOIDS];
Sprite sprites[NOOFBOIDS];

int main( int argc, char* args[] )
{
	

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	
	//Load media
	/*if (!LoadMedia())
	{
		printf("Failed to load media!\n");
	}*/

	

	time_t t1; // declare time variable  

	srand((unsigned)time(&t1)); // pass the srand() parameter  

	
	LoadBoids();
	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	// Rotation Angle
	double degrees = 0;
	// Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;



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
				case SDLK_ESCAPE:
					quit = true;
					break;
				
				case SDLK_w:
					flipType = SDL_FLIP_HORIZONTAL;
					
					break;
				case SDLK_s:
					flipType = SDL_FLIP_NONE;
					break;
				case SDLK_a:
					degrees -= 60;
					break;
				case SDLK_d:
					degrees += 60;
					break;
				}
			}
			topLeftButton.HandleEvent(&e);
		}

		// Clear the back buffer
		//SDL_RenderClear(gRenderer);

			

		//DrawFilledRectangle(gRenderer, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			
		//RenderTexture(gRenderer, gTexture, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 20, 30, 35);

			
		//

		//CreateViewPort(gRenderer, planTexture, 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		//CreateViewPort(gRenderer, planTexture, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		//CreateViewPort(gRenderer, planTexture, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			
		SetBackgroundColor(gRenderer, 156, 40, 49, 255);

		//backgroundTexture.Render(0, 0);
		//arrowTexture.Render(240, 190);

		//spriteSheetTexture.SetColor(r, g, b);

		//boidObject.transform.rotation += 10;



		
		for (int i = 0; i < NOOFBOIDS; i++)
		{
			tempBoidObjects[i].UpdateObject();
		}

		// Keyboard key sprites
		//spriteSheetTexture.SetAlpha(a);
		//spriteSheetTexture.Render(0, 0, &spriteClips[0], degrees, NULL, flipType);
		//spriteSheetTexture.Render((SCREEN_WIDTH - spriteClips[1].w * 4), 0, &spriteClips[1]);
		//spriteSheetTexture.Render(0, SCREEN_HEIGHT - spriteClips[2].h * 4, &spriteClips[2]);
		//spriteSheetTexture.Render(SCREEN_WIDTH - spriteClips[3].w * 4, SCREEN_HEIGHT - spriteClips[3].h * 4, &spriteClips[3]);

		//

		//// Render Current Frame
		//characterAnim.Animate(6);

		//textTexture.Render((SCREEN_WIDTH - textTexture.GetWidth()) / 2, (SCREEN_HEIGHT - textTexture.GetHeight()) / 2);

		//topLeftButton.Render();


		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	
	//Free resources and close SDL
	Close();

	getchar();
	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			//gScreenSurface = SDL_GetWindowSurface(gWindow);

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Init PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Init SDL TTF
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


SDL_Texture* LoadMediaOnTexture(const char* path)
{
	SDL_Texture* texture = NULL;
	//Loading success flag
	//bool success = true;
	
	//Load splash image
	//boidImage = SDL_LoadBMP("Sprites/flock_agent_sprite.bmp");
	//boidImage = SDL_LoadBMP(path);
	//boidImage = IMG_Load(path);
	texture = loadTexture(path);
	if (texture == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		//success = false;
	}

	return texture;
}

void Close()
{

	arrowTexture.Free();
	backgroundTexture.Free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(const char* path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	//Load Bitmap
	//SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	
	//Load PNGS
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, optimizedSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

SDL_Texture* loadTexture(const char* path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		// Clear old surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//Render texture to screen
void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height)
{
	SDL_Rect textureRect = { x, y, width, height };

	SDL_RenderCopy(renderer, texture, NULL, &textureRect);
}

void DrawFilledRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect redRect = { x, y, width, height };

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &redRect);

}


void SetBackgroundColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void CreateViewPort(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height)
{
	SDL_Rect viewPortRect = { x, y, width, height };
	SDL_RenderSetViewport(renderer, &viewPortRect);

	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

bool LoadMedia()
{
	bool success = true;

	if (!arrowTexture.LoadFromFile(gRenderer, "Sprites/up-arrow.png"))
	{
		printf("Failed to load arrow\n");
		success = false;
	}
	else
	{
		arrowTexture.SetScale(0.1f);
	}
	
	if (!backgroundTexture.LoadFromFile(gRenderer, "Sprites/Plan.png"))
	{
		printf("Failed to plan\n");
		success = false;
	}
	else
	{
		backgroundTexture.SetScale(0.75f);
	}

	if (!spriteSheetTexture.LoadFromFile(gRenderer, "Sprites/KeyboardBlack.png"))
	{

		printf("Failed to load spritesheet!\n");
		success = false;
	}
	else
	{
		// Escape key
		spriteClips[0].x = 27;
		spriteClips[0].y = 1;
		spriteClips[0].w = 20;
		spriteClips[0].h = 16;

		// 1 Key
		spriteClips[1].x = 48;
		spriteClips[1].y = 17;
		spriteClips[1].w = 16;
		spriteClips[1].h = 15;
		
		// 2 Key
		spriteClips[2].x = 64;
		spriteClips[2].y = 17;
		spriteClips[2].w = 16;
		spriteClips[2].h = 15;

		// 3 Key
		spriteClips[3].x = 80;
		spriteClips[3].y = 17;
		spriteClips[3].w = 16;
		spriteClips[3].h = 15;

		spriteSheetTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
		spriteSheetTexture.SetScale(4.0f);
	}

	characterAnim.LoadTexture(gRenderer, "Sprites/girlrun.png", 60, 60, 4, 8, 8);
	characterAnim.SetAnimPosition(300, SCREEN_HEIGHT / 2 - 64);
	characterAnim.SetAnimScale(2.0f);

	SDL_Color textColor = { 0, 0, 0 };
	if (!textTexture.LoadFromRenderedText(gRenderer, "Yoo!", textColor, "Fonts/FuturaBold.ttf", 50))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}

	topLeftButton.SetButtonSpriteTexture(gRenderer, "Sprites/PauseButton.png", 2);
	topLeftButton.SetPosition(100, 100);
	SDL_Rect clip1 = { 0, 0, 550, 500 };
	topLeftButton.SetTextureClip(0, &clip1);
	SDL_Rect clip2 = { 550, 0, 550, 500 };
	topLeftButton.SetTextureClip(1, &clip2);
	topLeftButton.SetDimensions(BUTTON_WIDTH, BUTTON_HEIGHT);
	topLeftButton.SetScale(0.25f);
	return success;
}

void LoadBoids()
{

	for (int i = 0; i < NOOFBOIDS; ++i)
	{
		// To generate a random number between min and max
		// int randNum = rand() % (max - min + 1) + min;

		int velX = rand() % (5 + 5 + 1) - 5;
		int velY = rand() % (5 + 5 + 1) - 5;

		velX = velX == 0 ? 1 : velX;
		velY = velY == 0 ? 1 : velY;
		//printf("Generated Random values: %d and %d", velX, velY);
		
		tempBoids[i].FindOtherBoids(tempBoids);
		tempBoids[i].SetVelocity(velX, velY);


		sprites[i].LoadSpriteTexture(gRenderer, "Sprites/up-arrow.png", 1);

		SDL_Point p;
		p.x = SCREEN_WIDTH / 2;
		p.y = SCREEN_HEIGHT / 2;
		tempBoidObjects[i].transform.position = p;
		tempBoidObjects[i].transform.scale = 0.1;
		tempBoidObjects[i].AddBehaviour(sprites[i]);
		tempBoidObjects[i].AddBehaviour(tempBoids[i]);
		tempBoidObjects[i].StartObject();
		tempBoidObjects[i].transform.position.x = rand() % (SCREEN_WIDTH - 0 + 1) + 0;
		tempBoidObjects[i].transform.position.y = rand() % (SCREEN_HEIGHT - 0 + 1) + 0;
		tempBoids[i].id = i;
	}



	

}
