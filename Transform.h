#pragma once
#include "Global.h"

class Transform
{
public:
	SDL_Point position;
	double rotation;
	double scale;
	Transform();
	Transform(SDL_Point position, double rotation, double scale);
};