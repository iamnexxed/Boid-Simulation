#include "Boid.h"
#include <stdio.h>
Boid::Boid()
{
	speed = 0;
}
Boid::Boid(int speed)
{
	this->speed = speed;
}
int Boid::GetSpeed()
{
	return speed;
}

void Boid::Start()
{
}

void Boid::Update()
{
	//printf("\nCalling update: %d, %d with speed %d", transform->position.x, transform->position.y, speed);
	SDL_Point p;
	p.x = speed;
	p.y = speed;
	transform->position -= p;
}

void Boid::Destroy()
{
}
