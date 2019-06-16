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
	Vec2f mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b) const;
	bool checkCircleCollision(CircleHitbox* a, CircleHitbox* b);
	static double distanceSquared(int x1, int y1, int x2, int y2);
	float checkSpeed(float velocity);
};
