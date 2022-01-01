#include "LTexture.h"


LTexture::LTexture()
{
	mTexture = NULL;
	textureRenderer = NULL;
	mWidth = 0;
	mHeight = 0;
	xPosition = 0;
	yPosition = 0;
	offsetX = 0;
	offsetY = 0;
	scale = 1.0f;
}

LTexture::~LTexture()
{
	Free();
}

bool LTexture::LoadFromFile(SDL_Renderer* renderer, const char* path)
{
	Free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		// Sets cyan as the transparent color
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
			offsetX = mWidth * scale / 2;
			offsetY = mHeight * scale / 2;
			printf("Loaded image : %s with width: %d, height: %d\n", path, mWidth, mHeight);
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	textureRenderer = renderer;
	return mTexture != NULL;


}

void LTexture::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		xPosition = 0;
		yPosition = 0;
		scale = 0.0f;
	}
}

bool LTexture::LoadFromRenderedText(SDL_Renderer* renderer, const char* text, SDL_Color textColor, const char* fontPath, int size)
{
	textureRenderer = renderer;
	// Get rid of preexisting texture
	Free();
	TTF_Font* fontText = TTF_OpenFont(fontPath, size);

	if (fontText == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(fontText, text, textColor);
	
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(textureRenderer, textSurface);
		if (mTexture == NULL)
		{

			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
			offsetX = mWidth * scale / 2;
			offsetY = mHeight * scale / 2;
		}
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;

	
}

void LTexture::Render(int x, int y, SDL_Rect* clip, double* angle, SDL_Point* center, SDL_RendererFlip flip)
{

	xPosition = x - offsetX;
	yPosition = y - offsetY;

	SDL_Rect renderQuad = { xPosition, yPosition, mWidth * scale, mHeight * scale };



	if (clip != NULL)
	{
		renderQuad.w = (int) (clip->w * scale);
		renderQuad.h = (int) (clip->h * scale);
	}

	SDL_RenderCopyEx(textureRenderer, mTexture, clip, &renderQuad, *angle, center, flip);
}

int LTexture::GetWidth()
{
	return mWidth;
}

int LTexture::GetHeight()
{
	return mHeight;
}

void LTexture::SetScale(double value)
{
	
	scale = value > 0.0f ? value : 1.0f;
	offsetX = mWidth * scale / 2;
	offsetY = mHeight * scale / 2;
}


void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::GetXPos()
{
	return xPosition;
}

int LTexture::GetYPos()
{
	return yPosition;
}

void LTexture::SetOffsetX(int value)
{
	offsetX = value;
}

void LTexture::SetOffsetY(int value)
{
	offsetY = value;
}
