#include "CollisionManager.h"
#include <iostream>


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::isColliding(GameObject *ball, GameObject *object)
{
	if (object->getHitbox() == nullptr)
		return false;

	CircleHitbox *circle = dynamic_cast<CircleHitbox*>(ball->getHitbox());
	LinesHitbox *lines = dynamic_cast<LinesHitbox*>(object->getHitbox());

	for (auto line : lines->hitlines)
	{
		float x1 = line.point1.x;
		float x2 = line.point2.x;
		float y1 = line.point1.y;
		float y2 = line.point2.y;

		float cx = circle->circle.x;
		float cy = circle->circle.y;
		float r = circle->circle.r;

		if (isPointInCircle(line.point1, cx, cy, r))
		{
			if(ball->isColliding == false && object->isColliding == false)
			{
				//ball->position = ball->position - Vec3f(0, 0, 0.1);
				Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
				Vec2f temp2 = mirrorVectorInLine(temp, line);
				ball->velocity = Vec3f(temp2.x, 0, temp2.y);
			}
			ball->isColliding = true;
			object->isColliding = true;
			return true;
		}
		else if (isPointInCircle(line.point2, cx, cy, r))
		{
			if (ball->isColliding == false && object->isColliding == false)
			{
				//ball->position = ball->position - Vec3f(0, 0, 0.1);
				std::cout << "kanker 2" << "\n";
				Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
				Vec2f temp2 = mirrorVectorInLine(temp, line);
				ball->velocity = Vec3f(temp2.x, 0, temp2.y);
			}
			ball->isColliding = true;
			object->isColliding = true;
			return true;
		}
			
		float length = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		float dot = (((cx - x1)*(x2 - x1)) + ((cy - y1)*(y2 - y1))) / pow(length,2);

		float closestX = x1 + (dot * (x2 - x1));
		float closestY = y1 + (dot * (y2 - y1));

		if (isPointOnLine(line.point1, line.point2, closestX, closestY))
		{
			float distX = closestX - cx;
			float distY = closestY - cy;
			float distance = sqrt(pow(distX, 2) + pow(distY, 2));
			if(distance <= r)
			{
				if (ball->isColliding == false && object->isColliding == false)
				{
					//ball->position = ball->position - Vec3f(0, 0, 0.1);
					std::cout << "kanker 3" << "\n";
					Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
					Vec2f temp2 = mirrorVectorInLine(temp, line);
					ball->velocity = Vec3f(temp2.x, 0, temp2.y);
				}
				ball->isColliding = true;
				object->isColliding = true;
				return true;
			}
		}
	}
	ball->isColliding = false;
	object->isColliding = false;
	return false;
}

bool CollisionManager::isPointOnLine(Vec2f point1, Vec2f point2, float px, float py)
{

	float x1 = point1.x;
	float x2 = point2.x;
	float y1 = point1.y;
	float y2 = point2.y;
	
	//get distance from the point tot the two end of the line
	float d1 = sqrt(pow((px - x1),2) + pow((py - y1), 2));
	float d2 = sqrt(pow((px - x2), 2) + pow((py - y2), 2));

	float length =  sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	float buffer = 0.1f;

	return d1 + d2 >= length - buffer && d1 + d2 <= length + buffer;
	
}

bool CollisionManager::isPointInCircle(Vec2f point, float cx, float cy, float r)
{
	float distX = point.x - cx;
	float distY = point.y - cy;

	float distance = sqrt(pow(distX, 2) + pow(distY, 2));

	return distance <= r;
}

Vec2f CollisionManager::mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b) const
{
	std::cout << "vector xy : " << d.x << "," << d.y << "\n";

	//this is our slop value.
	float slope = (b.point2.y - b.point1.y) / (b.point2.x - b.point1.x);

	//Then our normal value is
	::Vec2f n(slope, -1);

	//Our normal normalised
	::Vec2f normal(Vec2f::vectorNormalised(n));

	//Test Formula 2
	::Vec2f mirroredVec = d - 2 * normal * (Vec2f::vectorDotProduct(normal, d));

	std::cout << "Mirrored vector xy : " << mirroredVec.x << "," << mirroredVec.y << "\n";

	return mirroredVec;
}

