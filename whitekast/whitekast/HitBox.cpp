#include "Hitbox.h"

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

CircleHitbox::CircleHitbox(Vec3f pos, float d, Vec3f scale)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.y;
	circle.r = (d/2)*scale.x;
}

void CircleHitbox::shiftColliders(Vec3f pos)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.z;
}

LinesHitbox::LinesHitbox(std::vector<cv::Point> coordinates, Vec3f scale, float wkscale)
{
	lineHitbox = this;
	bool point1 = true;

	for (const cv::Point point : coordinates)
	{
		if(point1)
		{
			point1 = false;
			hitline.point1.x = (point.x*wkscale)*scale.x;
			hitline.point1.y = (point.y*wkscale)*scale.y;

		}
		else
		{
			point1 = true;
			hitline.point2.x = (point.x*wkscale)*scale.x;
			hitline.point2.y = (point.y*wkscale)*scale.y;

			hitlines.push_back(hitline);
		}
	}
}

void LinesHitbox::shiftColliders(Vec3f pos)
{
	for (Hitline line : hitlines)
	{
		line.point1.x += pos.x;
		line.point1.y += pos.y;

		line.point2.x += pos.x;
		line.point2.y += pos.y;
	}
}
