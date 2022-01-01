#include "GameObject.h"

GameObject::GameObject()
{
	behaviourCount = 0;
	
}

void GameObject::AddBehaviour(ObjectBehaviour& newBehaviour)
{
	newBehaviour.SetTransform(&transform);


	behaviours.insert(&newBehaviour);
	
	behaviourCount++;
}

int GameObject::GetBehaviourCount()
{
	return behaviourCount;
}

void GameObject::StartObject()
{
	std::unordered_set<ObjectBehaviour*>::iterator start;
	for (start = behaviours.begin(); start != behaviours.end(); start++)
	{
		start._Ptr->_Myval->Start();
	}
}


void GameObject::UpdateObject()
{
	std::unordered_set<ObjectBehaviour*>::iterator start;
	for (start = behaviours.begin(); start != behaviours.end(); start++)
	{
		start._Ptr->_Myval->Update();
	}
}

void GameObject::DestroyObject()
{
	std::unordered_set<ObjectBehaviour*>::iterator start;
	for (start = behaviours.begin(); start != behaviours.end(); start++)
	{
		start._Ptr->_Myval->Destroy();
	}
}

GameObject::~GameObject()
{
	behaviourCount = 0;
	behaviours.clear();

}