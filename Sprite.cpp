#include "Sprite.h"

Sprite::Sprite()
{
	clips = NULL;
	noOfSprites = 0;
	texture.Free();
}

Sprite::~Sprite()
{
	texture.Free();
	clips = NULL;
}

void Sprite::LoadSpriteTexture(SDL_Renderer* renderer, const char* path, int spriteCount)
{
	if (!texture.LoadFromFile(renderer, path))
	{

		printf("Failed to load texture : %s into sprite", path);

	}
	else
	{
		if (spriteCount > 1)
		{
			clips = new SDL_Rect[spriteCount];
			noOfSprites = spriteCount;
		}
		else
		{
			noOfSprites = 1;
		}
	}
	
}


void Sprite::SetClip(int index, SDL_Rect* rect)
{
	clips[index] = *rect;
}

SDL_Rect* Sprite::GetClip(int index)
{
	return &clips[index];
}

int Sprite::GetClipCount()
{
	return noOfSprites;
}

void Sprite::Render(int* x, int* y, SDL_Rect* clip, double* angle, SDL_Point* center, SDL_RendererFlip flip, double* scale)
{
	texture.SetScale(*scale);
	texture.Render(x, y, clip, angle, center, flip);
}


void Sprite::Start() 
{
}

void Sprite::Update()
{
	//printf("\nTransform position : %d, %d \n", transform->position.x, transform->position.y);
	Render(&transform->position.x, &transform->position.y, NULL,  &transform->rotation, NULL, SDL_FLIP_NONE, &transform->scale);
}

void Sprite::Destroy()
{
}

void Sprite::SetTextureScale(double value)
{

	texture.SetScale(value);
}