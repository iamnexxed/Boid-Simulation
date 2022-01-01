#include "Boid.h"



Boid::Boid()
{
	velocity.x = 0;
	velocity.y = 0;
}
Boid::Boid(int velocityX, int velocityY)
{
	velocity.x = velocityX;
	velocity.y = velocityY;
	
}
SDL_Point Boid::GetVelocity()
{
	return velocity;
}

void Boid::SetVelocity(int velocityX, int velocityY)
{
	velocity.x = velocityX;
	velocity.y = velocityY;
}

void Boid::ApplyRotation()
{
	SDL_FPoint v1(0.0f, -1.0f);
	SDL_FPoint v2;
	double magnitudeVel = std::pow(velocity.x, 2) + std::pow(velocity.y, 2);
	if (magnitudeVel > 0)
	{
		v2.x = velocity.x / std::sqrt(magnitudeVel);
		v2.y = velocity.y / std::sqrt(magnitudeVel);

	
		double magnitudeV1 = std::sqrt(std::pow(v1.x, 2) + std::pow(v1.y, 2));
		double magnitudeV2 = std::sqrt(std::pow(v2.x, 2) + std::pow(v2.y, 2));

		double aDotB = v1.x * v2.x + v1.y * v2.y;
		double cosT = aDotB / (magnitudeV1 * magnitudeV2);
		//cosT *= 180 / M_PI;
		double angle = std::acos(cosT) * 180 / M_PI;
		//printf("\nAngle of rotation:  %f ", angle);

		if (v2.x > 0)
			transform->rotation = angle;
		else
			transform->rotation = -angle;
	}
	

}

void Boid::Start()
{
	ApplyRotation();
}

void Boid::Update()
{
	

	ApplyRotation();

	transform->position += velocity;

	//ApplyRotation();

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
