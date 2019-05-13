#include "pch.h"
#include "WhitekastObject.h"

std::vector<Point> coordinates;
ObjectColor objectColor;

WhitekastObject::WhitekastObject(ObjectColor color) {
	objectColor = color;
}

WhitekastObject::~WhitekastObject() {}

std::vector<Point> WhitekastObject::getCoordinates()
{
	return coordinates;
}

void WhitekastObject::setCoordinates(std::vector<Point> newCoordinates)
{
	coordinates = newCoordinates;
}

ObjectColor WhitekastObject::getObjectColor()
{
	return objectColor;
}

void WhitekastObject::setObjectColor(ObjectColor color)
{
	objectColor = color;
}
