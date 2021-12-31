#include "Animation.h"

Animation::Animation()
{
	animationFrameCount = 0;
	currentFrame = 0;
	animClips = NULL;
	xAnimPos = 0;
	yAnimPos = 0;
}

Animation::~Animation()
{
	animationFrameCount = 0;
	currentFrame = 0;
	animClips = NULL;
	xAnimPos = 0;
	yAnimPos = 0;
	spriteSheetTexture.Free();
}

void Animation::LoadTexture(SDL_Renderer* renderer, const char* path, int frameWidth, int frameHeight, int rows, int columns, int totalSprites)
{

	animationFrameCount = totalSprites == 0 ? rows * columns : totalSprites;

	animClips = new SDL_Rect[animationFrameCount];

	if (!spriteSheetTexture.LoadFromFile(renderer, path))
	{

		printf("Failed to load spritesheet : %s",  path);
		
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (j + i * columns >= animationFrameCount)
				{
					break;
				}
				animClips[j + i * columns].x = frameWidth * j;
				animClips[j + i * columns].y = frameHeight * i;
				animClips[j + i * columns].w = frameWidth;
				animClips[j + i * columns].h = frameHeight;
			}

		}
	}
}

void Animation::Animate(int cyclesPerFrame)
{

	// Render Current Frame
	SDL_Rect* currentClip = &animClips[currentFrame / cyclesPerFrame];
	spriteSheetTexture.Render(&xAnimPos, &yAnimPos, currentClip);

	++currentFrame;
	if (currentFrame / cyclesPerFrame >= animationFrameCount)
	{
		currentFrame = 0;
	}
}

void Animation::SetAnimPosition(int x, int y)
{
	xAnimPos = x;
	yAnimPos = y;
}

void Animation::SetAnimScale(float value)
{
	spriteSheetTexture.SetScale(value);
}

void Animation::Start()
{
}

void Animation::Update()
{
}

void Animation::Destroy()
{
}
