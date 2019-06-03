#include "Hitbox.h"

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

CircleHitbox::CircleHitbox(Vec3f pos, float d)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.y;
	circle.r = (d/2);
}

Hitbox* CircleHitbox::getHitbox() const
{
	return cirlceHitbox;
}

void CircleHitbox::shiftColliders(Vec3f pos)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.z;
}

LinesHitbox::LinesHitbox(std::vector<cv::Point> coordinates, float scale)
{
	lineHitbox = this;
	bool point1 = true;

	for (const cv::Point point : coordinates)
	{
		if(point1)
		{
			point1 = false;
			hitline.point1.x = point.x*scale;
			hitline.point1.y = point.y*scale;

		}
		else
		{
			point1 = true;
			hitline.point2.x = point.x*scale;
			hitline.point2.y = point.y*scale;

			hitlines.push_back(hitline);
		}
	}
}

Hitbox* LinesHitbox::getHitbox() const
{
	return lineHitbox;
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
