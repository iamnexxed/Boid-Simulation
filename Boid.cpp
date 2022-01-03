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
	double magnitudeVel = GetMagnitude(point);
	if(magnitudeVel > 0)
		return SDL_FPoint(point.x / magnitudeVel, point.y / magnitudeVel);
	return SDL_FPoint();
}

double Boid::GetMagnitude(SDL_FPoint point)
{
	return std::sqrt(std::pow(point.x, 2) + std::pow(point.y, 2));
}

SDL_FPoint Boid::LimitMagnitude(SDL_FPoint direction, double limit)
{

	double magnitude = GetMagnitude(direction);
	SDL_FPoint unit = GetNormalized(direction);
	if (magnitude > limit)
	{
		return unit * limit;
	}

	return direction;
}

SDL_FPoint Boid::Separation()
{
	SDL_FPoint p(0, 0);
	SDL_FPoint average;
	int otherCount = 0;
	for (int i = 0; i < NOOFBOIDS; ++i)
	{
		if (others[i].id != this->id)
		{
			double dist = GetDistance(others[i]);
			if (dist < DETECTION_RADIUS)
			{
				SDL_FPoint oppDir;
				oppDir.x = transform->position.x - others[i].transform->position.x;
				oppDir.y = transform->position.y - others[i].transform->position.y;

				if(dist > 0)
					oppDir = oppDir / dist ;

				average += oppDir;


				otherCount++;
			}

		}
	}

	if (otherCount > 0)
	{
		average = average / otherCount;
		//we get a direction towards the velocity we want to achieve
		average = average - velocity;
		average = LimitMagnitude(average, SEPARATION_FORCE); // Need to limit the magnitude of velocity
		return average;
	}


	return p;
}

SDL_FPoint Boid::Alignment()
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
				average.x += others[i].GetVelocity().x;
				average.y += others[i].GetVelocity().y;
				otherCount++;
			}

		}
	}

	if (otherCount > 0)
	{
		average = average / otherCount;
		//we get a direction towards the velocity we want to achieve
		average = average - velocity;
		average = LimitMagnitude(average, ALIGNMENT_FORCE); // Need to limit the magnitude of velocity
		return average;
	}


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

		p = p - velocity;
		p = LimitMagnitude(p, COHESION_FORCE); // Need to limit the magnitude of velocity

		return p;
	}
	

	return p;
}

void Boid::ApplyRotation(SDL_FPoint direction)
{
	SDL_FPoint v1(0.0f, -1.0f);
	SDL_FPoint v2;
	double magnitudeVel = std::pow(direction.x, 2) + std::pow(direction.y, 2);
	if (magnitudeVel > 0)
	{
		v2.x = direction.x / std::sqrt(magnitudeVel);
		v2.y = direction.y / std::sqrt(magnitudeVel);

	
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
	
}

void Boid::Update()
{
	


	SDL_FPoint s = Separation();
	SDL_FPoint a = Alignment();
	SDL_FPoint c = Cohesion();

	SDL_FPoint acceleration;
	

	acceleration += s;
	acceleration += a;
	acceleration += c;

	printf("\nGot acceleration for boid : %d at %f, %f", id, acceleration.x, acceleration.y);
	
	transform->position.x += (velocity.x);
	transform->position.y += (velocity.y);

	velocity += acceleration;

	velocity = GetNormalized(velocity) * BOID_SPEED;

	ApplyRotation(velocity);

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
