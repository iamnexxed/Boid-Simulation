#pragma once
#include "ObjectBehaviour.h"

class Boid : public ObjectBehaviour
{

private:
	
	SDL_Point velocity;
	void ApplyRotation();

public:
	Boid();
	Boid(int velocityX, int velocityY);
	SDL_Point GetVelocity();
	void SetVelocity(int velocityX, int velocityY);

	void Start() override;
	void Update() override;
	void Destroy() override;
};