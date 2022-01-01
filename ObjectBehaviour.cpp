#include "ObjectBehaviour.h"

ObjectBehaviour::ObjectBehaviour()
{
	transform = nullptr;
}

ObjectBehaviour::~ObjectBehaviour()
{
	transform = nullptr;
}

void ObjectBehaviour::SetTransform(Transform* transform)
{
	this->transform = transform;
}
