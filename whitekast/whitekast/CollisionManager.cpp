#include <iostream>
#include "CollisionManager.h"

#include "CollisionManager.h"
#include "PointCounter.h"
#include "AudioManager.h"

CollisionManager::CollisionManager() { }

CollisionManager::~CollisionManager() { }

bool CollisionManager::isColliding(GameObject *ball, GameObject *object)
{
	if (object->getHitbox() == nullptr)
		return false;

	CircleHitbox* circleball = dynamic_cast<CircleHitbox*>(ball->getCircleBox());
	CircleHitbox* circleobject = dynamic_cast<CircleHitbox*>(object->getCircleBox());

	// check if the circle collide, then enter loop. This increases performance
	if (checkCircleCollision(circleball, circleobject))
	{
		CircleHitbox *circle = dynamic_cast<CircleHitbox*>(ball->getHitbox());
		LinesHitbox *lines = dynamic_cast<LinesHitbox*>(object->getHitbox());

		for (auto line : lines->hitlines)
		{
			float x1 = line.point1.x,
				x2 = line.point2.x,
				y1 = line.point1.y,
				y2 = line.point2.y;

			float cx = circle->circle.x,
				cy = circle->circle.y,
				r = circle->circle.r;

			if (isPointInCircle(line.point1, cx, cy, r))
			{
				if (ball->isColliding == false && object->isColliding == false)
				{
					Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z),
						temp2 = mirrorVectorInLine(temp, line);

					temp2 = checkSpeed(temp2, object);

					ball->velocity = Vec3f(temp2.x, 0, temp2.y);

					if (object->bounceFactor == 1.5)
					{
						PointCounter::getInstance()->hitBumper();
						AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
					}
					else if (object->bounceFactor == 1.0)
					{
						PointCounter::getInstance()->hitSpecial();
						AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
					}
				}

				ball->isColliding = true;
				object->isColliding = true;

				return true;
			}
			else if (isPointInCircle(line.point2, cx, cy, r))
			{
				if (ball->isColliding == false && object->isColliding == false)
				{
					Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z),
						temp2 = mirrorVectorInLine(temp, line);

					temp2 = checkSpeed(temp2, object);

					ball->velocity = Vec3f(temp2.x, 0, temp2.y);

					if(object->bounceFactor == 1.5)
					{
						PointCounter::getInstance()->hitBumper();
						AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
					}
					else if (object->bounceFactor == 1.0)
					{
						PointCounter::getInstance()->hitSpecial();
						AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
					}
				}

				ball->isColliding = true;
				object->isColliding = true;
				
				return true;
			}

			float length = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)),
				dot = (((cx - x1)*(x2 - x1)) + ((cy - y1)*(y2 - y1))) / pow(length, 2);

			float closestX = x1 + (dot * (x2 - x1)),
				closestY = y1 + (dot * (y2 - y1));

			if (isPointOnLine(line.point1, line.point2, closestX, closestY))
			{
				float distX = closestX - cx,
					distY = closestY - cy,
					distance = sqrt(pow(distX, 2) + pow(distY, 2));
				if (distance <= r)
				{
					if (ball->isColliding == false && object->isColliding == false)
					{
						Vec2f temp = Vec2f(ball->velocity.x, ball->velocity.z),
							temp2 = mirrorVectorInLine(temp, line);

						temp2 = checkSpeed(temp2, object);

						ball->velocity = Vec3f(temp2.x, 0, temp2.y);
						if (object->bounceFactor == 1.5)
						{
							PointCounter::getInstance()->hitBumper();
							AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
						}
						else if (object->bounceFactor == 1.0)
						{
							PointCounter::getInstance()->hitSpecial();
							AudioManager::getInstance()->playSound("audio/bumper_hit.wav");
						}
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
	float x1 = point1.x,
		x2 = point2.x,
		y1 = point1.y,
		y2 = point2.y;
	
	// get distance from the point tot the two end of the line
	float d1 = sqrt(pow((px - x1),2) + pow((py - y1), 2)),
		d2 = sqrt(pow((px - x2), 2) + pow((py - y2), 2));

	float length =  sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	float buffer = 0.1f;

	return d1 + d2 >= length - buffer && d1 + d2 <= length + buffer;
}

bool CollisionManager::isPointInCircle(Vec2f point, float cx, float cy, float r)
{
	float distX = point.x - cx,
		distY = point.y - cy;

	float distance = sqrt(pow(distX, 2) + pow(distY, 2));

	return distance <= r;
}

Vec2f CollisionManager::mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b) const
{
	std::cout << "vector xy : " << d.x << "," << d.y << "\n";
	std::cout << "point1 xy : " << b.point1.x << "," << b.point1.y << "\n";
	std::cout << "point2 xy : " << b.point2.x << "," << b.point2.y << "\n";

	// this is our slop value.
	float slope = (b.point2.y - b.point1.y) / (b.point2.x - b.point1.x);

	// test
	float dx = b.point2.x - b.point1.x,
		dy = b.point2.y - b.point1.y;

	// then our normal value is
	::Vec2f n(dy, -dx);

	// our normal normalised
	::Vec2f normal(Vec2f::vectorNormalised(n));

	// test Formula 2
	::Vec2f mirroredVec = d - 2 * normal * (Vec2f::vectorDotProduct(normal, d));

	std::cout << "Mirrored vector xy : " << mirroredVec.x << "," << mirroredVec.y << "\n";

	return mirroredVec;
}

bool CollisionManager::checkCircleCollision(CircleHitbox* a, CircleHitbox* b)
{
	// calculate total radius squared
	float totalRadiusSquared = a->circle.r + b->circle.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	// if the distance between the centers of the circles is less than the sum of their radii
	if (distanceSquared(a->circle.x, a->circle.y, b->circle.x, b->circle.y) < totalRadiusSquared)
	{
		// the circles have collided
		return true;
	}

	// if not
	return false;
}

float CollisionManager::distanceSquared(float x1, float y1, float x2, float y2)
{
	float deltaX = x2 - x1;
	float deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

Vec2f CollisionManager::checkSpeed(Vec2f b, GameObject *object)
{
	if(b.magnitude() > 0.3 && b.magnitude() < 3)
	{
		b = b * object->bounceFactor;
	}

	return b;
}

