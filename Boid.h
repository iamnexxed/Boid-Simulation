#pragma once
#include "ObjectBehaviour.h"

class Boid : public ObjectBehaviour
{

private:
	
	SDL_FPoint velocity;
	void ApplyRotation();
	Boid* others;

public:
	int id;
	Boid();
	Boid(int id);
	Boid(int velocityX, int velocityY);
	SDL_FPoint GetVelocity();
	void SetVelocity(int velocityX, int velocityY);
	void FindOtherBoids(Boid* boids);
	int GetDistance(Boid other);
	SDL_FPoint GetNormalized(SDL_FPoint point);

	SDL_FPoint Separation();
	SDL_FPoint Alignment();
	SDL_FPoint Cohesion();

	void Start() override;
	void Update() override;
	void Destroy() override;
};