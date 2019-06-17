#include "CollisionManager.h"
#include <iostream>
#include "FlipComponent.h"

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

	CircleHitbox* circleball = dynamic_cast<CircleHitbox*>(ball->getCircleBox());
	CircleHitbox* circleobject = dynamic_cast<CircleHitbox*>(object->getCircleBox());

	//Check if the circle collide, then enter loop. This increases performance
	//checkCircleCollision(circleball, circleobject)
	if(true)
	{
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
				if (ball->isColliding == false && object->isColliding == false)
				{
					std::cout << "collision 1" << "\n";
					Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
					Vec2f temp2 = mirrorVectorInLine(temp, line);

					temp2 = checkSpeed(temp2, object);

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
					std::cout << "collision 2" << "\n";
					Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
					Vec2f temp2 = mirrorVectorInLine(temp, line);

					temp2 = checkSpeed(temp2, object);

					ball->velocity = Vec3f(temp2.x, 0, temp2.y);
					
				}
				ball->isColliding = true;
				object->isColliding = true;
				return true;
			}

			float length = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
			float dot = (((cx - x1)*(x2 - x1)) + ((cy - y1)*(y2 - y1))) / pow(length, 2);

			float closestX = x1 + (dot * (x2 - x1));
			float closestY = y1 + (dot * (y2 - y1));

			if (isPointOnLine(line.point1, line.point2, closestX, closestY))
			{
				float distX = closestX - cx;
				float distY = closestY - cy;
				float distance = sqrt(pow(distX, 2) + pow(distY, 2));
				if (distance <= r)
				{
					if (ball->isColliding == false && object->isColliding == false)
					{
						std::cout << "collision 3" << "\n";
						Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z);
						Vec2f temp2 = mirrorVectorInLine(temp, line);

						temp2 = checkSpeed(temp2, object);

						ball->velocity = Vec3f(temp2.x, 0, temp2.y);
					}
					ball->isColliding = true;
					object->isColliding = true;
					return true;
				}
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
	std::cout << "point1 xy : " << b.point1.x << "," << b.point1.y << "\n";
	std::cout << "point2 xy : " << b.point2.x << "," << b.point2.y << "\n";

	//this is our slop value.
	float slope = (b.point2.y - b.point1.y) / (b.point2.x - b.point1.x);

	//test
	float dx = b.point2.x - b.point1.x;
	float dy = b.point2.y - b.point1.y;

	//Then our normal value is
	::Vec2f n(dy, -dx);

	//Our normal normalised
	::Vec2f normal(Vec2f::vectorNormalised(n));

	//Test Formula 2
	::Vec2f mirroredVec = d - 2 * normal * (Vec2f::vectorDotProduct(normal, d));

	std::cout << "Mirrored vector xy : " << mirroredVec.x << "," << mirroredVec.y << "\n";

	return mirroredVec;
}

bool CollisionManager::checkCircleCollision(CircleHitbox* a, CircleHitbox* b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a->circle.r + b->circle.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	if (distanceSquared(a->circle.x, a->circle.y, b->circle.x, b->circle.y) < (totalRadiusSquared))
	{
		//The circles have collided
		return true;
	}

	//If not
	return false;
}

double CollisionManager::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

Vec2f CollisionManager::checkSpeed(Vec2f b, GameObject *object)
{
	if(b.magnitude() >= 0.8f && b.magnitude() <= 3.0f)
	{
		b = b * object->bounceFactor;
	}
	return b;
}

