#pragma once
#include <SDL.h>
#include "Transform.h"

class ObjectBehaviour
{
protected:
	Transform* transform;
	
public:
	ObjectBehaviour();
	~ObjectBehaviour();
	void SetTransform(Transform* transform);
	
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};
