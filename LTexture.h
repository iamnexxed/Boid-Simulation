#pragma once

#include "Global.h"

class LTexture 
{
private:
	// Texture stored on hardware
	SDL_Texture* mTexture;

	SDL_Renderer* textureRenderer;

	// Image Coordinates
	int xPosition;
	int yPosition;

	// Image dimensions
	int mWidth;
	int mHeight;

	// Image offset
	int offsetX;
	int offsetY;

	float scale;

public:
	LTexture();
	~LTexture();

	bool LoadFromFile(SDL_Renderer* renderer, const char* path);

	bool LoadFromRenderedText(SDL_Renderer* renderer, const char* text, SDL_Color textColor, const char* fontPath, int size);

	void Free();
	void Render(int x, int y, SDL_Rect* clip = NULL, double* angle = nullptr, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth();
	int GetHeight();

	int GetXPos();
	int GetYPos();

	void SetOffsetX(int value);
	void SetOffsetY(int value);

	void SetScale(double value);

	// Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set Blending
	void SetBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void SetAlpha(Uint8 alpha);
};