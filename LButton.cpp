#include "LButton.h"


LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::SetPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::SetDimensions(int width, int height)
{
	buttonWidth = width;
	buttonHeight = height;
	//buttonImageTexture.SetTextureScale()
}

void LButton::SetScale(float value)
{
	buttonImageSprite.SetTextureScale(value);
}

int LButton::GetWidth()
{
	return buttonWidth;
}

int LButton::GetHeight()
{
	return buttonHeight;
}

void LButton::SetButtonSpriteTexture(SDL_Renderer* renderer, const char* path, int spriteCount)
{
	
	buttonImageSprite.LoadSpriteTexture(renderer, path, spriteCount);
}


void LButton::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check is mouse is in the button
		bool isInside = true;

		// Mouse is left of button
		if (x < mPosition.x)
		{
			isInside = false;
		}
		else if (x > mPosition.x + buttonWidth)
		{
			isInside = false;
		}
		else if (y < mPosition.y)
		{
			isInside = false;
		}
		else if (y > mPosition.y + buttonHeight)
		{
			isInside = false;
		}

		if (!isInside)
		{
			currentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
			case SDL_MOUSEBUTTONUP:
				currentSprite = BUTTON_SPRITE_MOUSE_UP;
			default:
				break;
			}
		}
	}
}


Sprite* LButton::GetButtonSprite()
{
	return &buttonImageSprite;
}

void LButton::Start()
{
}

void LButton::Update()
{
}

void LButton::Destroy()
{
}


void LButton::SetTextureClip(int index, SDL_Rect* rect)
{
	buttonImageSprite.SetClip(index, rect);
}

void LButton::Render()
{
	if(buttonImageSprite.GetClipCount() > 0)
		buttonImageSprite.Render(mPosition.x, mPosition.y, buttonImageSprite.GetClip(currentSprite));
	else
		printf("Sprite sheet on button has no clips!");
}