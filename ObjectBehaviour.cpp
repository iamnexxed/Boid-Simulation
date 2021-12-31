#include "ObjectBehaviour.h"
#include <stdio.h>
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
void ObjectBehaviour::Start()
{
}

void ObjectBehaviour::Update()
{
	//printf("\nCalled from Base!\n");
}

void ObjectBehaviour::Destroy()
{
}