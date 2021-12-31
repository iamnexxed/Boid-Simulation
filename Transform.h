#pragma once
#include <SDL.h>

class Transform
{
public:
	SDL_Point position;
	double rotation;
	double scale;
	Transform();
	Transform(SDL_Point position, double rotation, double scale);
};