#include "Boid.h"

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
	

	SDL_Point p(rand() % speed - speed, -speed);

	transform->position += p;
	if (transform->position.x <= 0)
	{
		transform->position.x = SCREEN_WIDTH;
	}
	else if (transform->position.x > SCREEN_WIDTH)
	{
		transform->position.x = 0;
	}

	if (transform->position.y <= 0)
	{
		transform->position.y = SCREEN_HEIGHT;
	}
	else if (transform->position.y > SCREEN_HEIGHT)
	{
		transform->position.y = 0;
	}

}

void Boid::Destroy()
{
}
