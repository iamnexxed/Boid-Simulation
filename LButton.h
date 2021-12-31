#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "ObjectBehaviour.h"

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_MOUSE_TOTAL = 4
};

class LButton : public ObjectBehaviour
{
private:
	SDL_Point mPosition;
	Sprite buttonImageSprite;
	LButtonSprite currentSprite;
	int buttonWidth;
	int buttonHeight;

public:
	LButton();
	void SetButtonSpriteTexture(SDL_Renderer* renderer, const char* path, int spriteCount = 1);
	void SetPosition(int x, int y);
	void SetTextureClip(int index, SDL_Rect* rect);
	void SetDimensions(int width, int height);
	void SetScale(float value);

	void HandleEvent(SDL_Event* e);
	void Render();

	int GetWidth();
	int GetHeight();
	Sprite* GetButtonSprite();
	
	void Start();
	void Update();
	void Destroy();
	
};