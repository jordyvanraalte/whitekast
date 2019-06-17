/*
	HitBox
	Purpose: The object the pinball will collide with and react to.

	@version 1.1 - 2019/06/03
*/

#pragma once

#include <list>
#include <vector>
#include <opencv2/core/affine.hpp>
#include "Vec.h"


class Hitbox
{
public:
	Hitbox();
	~Hitbox();

	/*
		Shifts the hitbox's position to the position of the hitbox's object.

		@param Vec3f pos - The new hitbox position.
		@return void.
	*/
	virtual void shiftColliders(::Vec3f pos) = 0;

	/*
		Flips the hitbox's position to the position of the hitbox's object.

		@param Vec3f pos - The new hitbox position.
		@return void.
	*/
	virtual void flipColliders(::Vec3f pos) { };
	
	/*
		Draws the hitboxes for debugging purposes.

		@param -
		@return void.
	*/
	virtual void drawColliders() = 0;
};

class CircleHitbox : public Hitbox
{
public:
	struct Circle
	{
		float x, y, r;
	};

	CircleHitbox* cirlceHitbox;
	Circle circle;

	CircleHitbox();
	CircleHitbox(::Vec3f pos, float radius, ::Vec3f scale); 
	~CircleHitbox();

	void drawColliders() override;
	void shiftColliders(::Vec3f pos) override;
};

class LinesHitbox : public Hitbox
{
public:
	struct Hitline
	{
		::Vec2f point1;
		::Vec2f point2;
	};

	LinesHitbox* lineHitbox;
	Hitline hitline;
	std::vector<Hitline> hitlines;

	LinesHitbox();
	LinesHitbox(std::vector<cv::Point> coordinates, ::Vec3f scale, float wkscale);
	~LinesHitbox();

	void drawColliders() override;
	void shiftColliders(::Vec3f pos) override;
	void flipColliders(::Vec3f pos) override;
};
