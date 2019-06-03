#pragma once
#include "Vec.h"

class GameObject;

class Component
{
protected:
	GameObject* gameObject;
public:
	explicit Component();
	virtual ~Component();

	virtual void update(float elapsedTime) {};
	virtual void handleEvent(float elapsedTime) {};
	virtual void setHandle(bool handle) {};
	virtual inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

