#pragma once
#include "ObjectBehaviour.h"

class Boid : public ObjectBehaviour
{

private:
	int speed = 3;


public:
	Boid();
	Boid(int speed);
	int GetSpeed();

	void Start() override;
	void Update() override;
	void Destroy() override;
};