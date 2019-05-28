#pragma once
#include "GameObject.h"
#include "HitBox.h"

class CollisionManager
{
private:
	bool isPointOnLine(Vec2f point1, Vec2f point2, float px, float py);

public:
	CollisionManager();
	~CollisionManager();

	bool isColliding(GameObject bal, GameObject object);
};

