#pragma once
#include <list>
#include "Vec.h"
#include <vector>
#include <opencv2/core/affine.hpp>

class Hitbox
{

public:

	Hitbox();
	~Hitbox();

	virtual void shiftColliders(::Vec3f pos) = 0;
	virtual void flipColliders(::Vec3f pos) {};

};

class CircleHitbox : public Hitbox
{


public:

	CircleHitbox* cirlceHitbox;

	struct Circle
	{
		float x, y, r;
	};

	Circle circle;

	CircleHitbox();
	CircleHitbox(::Vec3f pos, float radius, ::Vec3f scale); 
	~CircleHitbox();

	void shiftColliders(::Vec3f pos) override;
};

class LinesHitbox : public Hitbox
{

public:

	LinesHitbox* lineHitbox;

public:

	struct Hitline
	{
		::Vec2f point1;
		::Vec2f point2;
	};

	std::vector<Hitline> hitlines;

	LinesHitbox();
	LinesHitbox(std::vector<cv::Point> coordinates, ::Vec3f scale, float wkscale);
	~LinesHitbox();

	Hitline hitline;

	void shiftColliders(::Vec3f pos) override;
	void flipColliders(::Vec3f pos) override;
};
