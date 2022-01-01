#pragma once
#include "Global.h"
#include "Transform.h"


class ObjectBehaviour
{
protected:
	Transform* transform;
	
public:
	ObjectBehaviour();
	~ObjectBehaviour();
	void SetTransform(Transform* transform);
	
	// Virtual Function: https://en.wikipedia.org/wiki/Virtual_function#C.2B.2B

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};
