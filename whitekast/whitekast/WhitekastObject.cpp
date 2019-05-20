#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "GL/freeglut.h"

std::vector<Point> coordinates;
Point center;
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

Point WhitekastObject::getCenter()
{
	return center;
}

void WhitekastObject::setCenter(Point centerPoint)
{
	center = centerPoint;
}

ObjectColor WhitekastObject::getObjectColor()
{
	return objectColor;
}

void WhitekastObject::setObjectColor(ObjectColor color)
{
	objectColor = color;
}

void WhitekastObject::setDrawingColor()
{
	switch (objectColor) {
	case RED:
		glColor3f(1, 0, 0);
		break;
	case GREEN:
		glColor3f(0, 1, 0);
		break;
	case BLUE:
		glColor3f(0, 0, 1);
		break;
	}
}

void WhitekastObject::draw() {
	glBegin(GL_TRIANGLE_STRIP);
	setDrawingColor();
	for (int i = 0; i < coordinates.size() - 1; i++) {
		glVertex3f(coordinates[i].x / CAMERA_WIDTH, -2, coordinates[i].y / CAMERA_HEIGHT);
		glVertex3f(coordinates[i + 1].x / CAMERA_WIDTH, -2, coordinates[i + 1].y / CAMERA_HEIGHT);
		glVertex3f(center.x / CAMERA_WIDTH, -2, center.y / CAMERA_HEIGHT);
	}
	float lastX = coordinates[coordinates.size() - 1].x / CAMERA_WIDTH;
	float lastY = coordinates[coordinates.size() - 1].y / CAMERA_HEIGHT;
	glVertex3f(lastX, -2, lastY);
	glVertex3f(coordinates[0].x / CAMERA_WIDTH, -2, coordinates[0].y / CAMERA_HEIGHT);
	glVertex3f(center.x / CAMERA_WIDTH, -2, center.y / CAMERA_HEIGHT);
	glEnd();
}
