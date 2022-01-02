#pragma once
#include "ObjectBehaviour.h"

class Boid : public ObjectBehaviour
{

private:
	
	SDL_Point velocity;
	void ApplyRotation();
	Boid* others;

public:
	Boid();
	Boid(int velocityX, int velocityY);
	SDL_Point GetVelocity();
	void SetVelocity(int velocityX, int velocityY);
	void FindOtherBoids(Boid* boids);

	SDL_Point Separation();
	SDL_Point Alignment();
	SDL_Point Cohesion();

	void Start() override;
	void Update() override;
	void Destroy() override;
};