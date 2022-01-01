#pragma once

#include "ObjectBehaviour.h"
#include "Transform.h"

class GameObject
{
private:
	int behaviourCount = 0;
	std::unordered_set<ObjectBehaviour*> behaviours;

public:
	Transform transform;

	GameObject();
	~GameObject();
	void AddBehaviour(ObjectBehaviour& newBehaviour);
	int GetBehaviourCount();
	void UpdateObject();

};