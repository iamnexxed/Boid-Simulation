#pragma once

#include "LTexture.h"
#include <SDL.h>
#include "ObjectBehaviour.h"

class Sprite : public ObjectBehaviour
{
private:
	LTexture texture;
	SDL_Rect* clips;
	int noOfSprites;
	int offsetX;
	int offsetY;

public:
	Sprite();
	~Sprite();
	void LoadSpriteTexture(SDL_Renderer* renderer, const char* path, int spriteCount = 1);
	void SetClip(int index, SDL_Rect* rect);
	SDL_Rect* GetClip(int index);
	int GetClipCount();
	void SetTextureScale(double value);
	void Render(int* x, int* y, SDL_Rect* clip = NULL, double* angle = nullptr, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, double* scale = nullptr);


	void Start() override;
	void Update() override;
	void Destroy() override;

};