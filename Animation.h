#pragma once
#include "LTexture.h"
#include <SDL.h>
#include "ObjectBehaviour.h"

class Animation : public ObjectBehaviour
{
private:

	LTexture spriteSheetTexture;
	int animationFrameCount;
	SDL_Rect* animClips;
	
	int currentFrame;
	int xAnimPos;
	int yAnimPos;

public:
	Animation();
	~Animation();
	void LoadTexture(SDL_Renderer* renderer, const char* path, int frameWidth, int frameHeight, int rows, int columns, int totalSprites = 0);
	void Animate(int cyclesPerFrame);
	void SetAnimPosition(int x, int y);
	void SetAnimScale(float value);
	void Start();
	void Update();
	void Destroy();
};