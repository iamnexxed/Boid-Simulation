#include "Boid.h"



Boid::Boid()
{
	velocity.x = 0;
	velocity.y = 0;
	id = -1;
	others = nullptr;
}
Boid::Boid(int id)
{
	velocity.x = 0;
	velocity.y = 0;
	this->id = id;
	others = nullptr;
}
Boid::Boid(int velocityX, int velocityY)
{
	id = -1;
	velocity.x = velocityX;
	velocity.y = velocityY;
	others = nullptr;
}
SDL_FPoint Boid::GetVelocity()
{
	return velocity;
}

void Boid::SetVelocity(int velocityX, int velocityY)
{
	velocity.x = velocityX;
	velocity.y = velocityY;
}

void Boid::FindOtherBoids(Boid* boids)
{
	others = boids;
}

int Boid::GetDistance(Boid other)
{
	SDL_Point dir = transform->position - other.transform->position;
	SDL_FPoint fDir(dir.x, dir.y);
	return std::sqrt(std::pow(fDir.x, 2) + std::pow(fDir.y, 2));
}

SDL_FPoint Boid::GetNormalized(SDL_FPoint point)
{
	double magnitudeVel = std::pow(point.x, 2) + std::pow(point.y, 2);
	if(magnitudeVel > 0)
		return SDL_FPoint(point.x / std::sqrt(magnitudeVel), point.y / std::sqrt(magnitudeVel));
	return SDL_FPoint();
}

SDL_FPoint Boid::Separation()
{
	SDL_FPoint p;
	return p;
}

SDL_FPoint Boid::Alignment()
{
	SDL_FPoint p;
	return p;
}

SDL_FPoint Boid::Cohesion()
{
	SDL_FPoint p(0, 0);
	SDL_FPoint average;
	int otherCount = 0;
	for (int i = 0; i < NOOFBOIDS; ++i)
	{
		if (others[i].id != this->id)
		{
			if (GetDistance(others[i]) < DETECTION_RADIUS)
			{
				average.x += others[i].transform->position.x;
				average.y += others[i].transform->position.y;
				otherCount++;
			}
			
		}
	}

	if (otherCount > 0)
	{
		average = average / otherCount;
		p.x = average.x - transform->position.x;
		p.y = average.y - transform->position.y;
		p = GetNormalized(p);

		return p * STEERING_FORCE;
	}
	

	return p;
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

		double aDotB = (double)v1.x * v2.x + (double)v1.y * v2.y;
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

	SDL_FPoint s = Separation();
	SDL_FPoint a = Alignment();
	SDL_FPoint c = Cohesion();

	SDL_FPoint acceleration;
	

	acceleration += s;
	acceleration += a;
	acceleration += c;

	printf("\nGot acceleration for boid : %d at %f, %f", id, acceleration.x, acceleration.y);

	velocity += acceleration;

	transform->position.x += (velocity.x);
	transform->position.y += (velocity.y);

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
