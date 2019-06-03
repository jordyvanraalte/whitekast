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

	bool isColliding(GameObject *ball, GameObject *object);
	bool isPointInCircle(Vec2f point, float cx, float cy, float r);
	::Vec2f mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b);
};
