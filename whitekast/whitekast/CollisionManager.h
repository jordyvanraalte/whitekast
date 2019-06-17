/*
	CollisionManager
	Purpose: Handles collision detection.

	@version 1.2 - 2019/06/03
*/

#pragma once

#include "GameObject.h"
#include "HitBox.h"


class CollisionManager
{
private:
	/*
		Returns true or false wether the pinball is colliding with the given line.

		@param Vec2f point1 - First point of the given line.
		@param Vec2f point2 - Second point of the given line.
		@param float px - The pinball's x co�rdinate.
		@param float py - The pinball's y co�rdinate.
		@return bool.
	*/
	bool isPointOnLine(Vec2f point1, Vec2f point2, float px, float py);

public:
	CollisionManager();
	~CollisionManager();

	/*
		Returns true or false wether the pinball is colliding with the given object.

		@param GameObject *bal - The pinball.
		@param GameObject *object - The collision object.
		@return bool.
	*/
	bool isColliding(GameObject *ball, GameObject *object);

	/*
		Returns true or false wether the given point is within the given circle.

		@param Vec2f point - The given circle.
		@param float cx - The x co�rdinate of the circle's center point.
		@param float cy - The y co�rdinate of the circle's center point.
		@param float r - Radius of the given circle.
		@return bool.
	*/
	bool isPointInCircle(Vec2f point, float cx, float cy, float r);
	Vec2f mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b, GameObject* obj) const;

	/*
		Returns a mirrored version of a given vector in a given hitbox line.

		@param Vec2f d - The line to be mirrored.
		@param Hitline b - The given line to be mirrored in.
		@return Vec2f.
	*/
	Vec2f mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b) const;

	/*
		Returns whether two hitboxes collide.

		@param CircleHitbox* a - Circle hitbox 1.
		@param CircleHitbox* b - Circle hitbox 2.
		@return bool.
	*/
	bool checkCircleCollision(CircleHitbox* a, CircleHitbox* b);

	/*
		Returns the distance between two points.

		@param float x1 - X-coördinate of first point.
		@param float y1 - Y-coördinate of first point.
		@param float x2 - X-coördinate of second point.
		@param float y2 - Y-coördinate of second point.
		@return Vec2f.
	*/
	static float distanceSquared(float x1, float y1, float x2, float y2);

	/*
		Returns the speed * a bounce factor from a given object.

		@param Vec2f b - A speed vector.
		@param GameObject* object - A game object.
		@return Vec2f.
	*/
	Vec2f checkSpeed(Vec2f b, GameObject* object);
};
