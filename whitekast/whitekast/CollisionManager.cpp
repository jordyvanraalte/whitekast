#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::isColliding(GameObject bal, GameObject object)
{
	CircleHitbox *circle = dynamic_cast<CircleHitbox*>(bal.getHitbox());
	LinesHitbox *lines = dynamic_cast<LinesHitbox*>(object.getHitbox());

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
			return true;
		else if (isPointInCircle(line.point2, cx, cy, r))
			return true;



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
				return true;
		}
	}
	return false;
}

bool CollisionManager::isPointInLine(Vec2f point1, Vec2f point2, float px, float py)
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

bool isPointInCircle(Vec2f point, float cx, float cy, float r)
{
	float distX = point.x - cx;
	float distY = point.y - cy;

	float distance = sqrt(pow(distX, 2) + pow(distY, 2));

	return distance <= r;
}