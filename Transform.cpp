#include "Transform.h"
#include <stdio.h>
Transform::Transform()
{
	SDL_Point p;
	p.x = 0;
	p.y = 0;
	this->position = p;

	rotation = 0.0f;

	p.x = 1;
	p.y = 1;

	this->scale = 0;
}

Transform::Transform(SDL_Point position, double rotation, double scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}