#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "DrawComponent.h"
#include "GL/freeglut.h"

std::vector<Point> coordinates;
Point center;
ObjectColor objectColor;

WhitekastObject::WhitekastObject(ObjectColor color) : DrawComponent() {
	
	objectColor = color;
}

WhitekastObject::~WhitekastObject() {}

std::vector<Point> WhitekastObject::getCoordinates()
{
	return coordinates;
}

void WhitekastObject::setCoordinates(std::vector<Point> newCoordinates)
{
	//coordinates = newCoordinates;
	for (int i = 0; i < newCoordinates.size(); i += 2) {
		coordinates.push_back(newCoordinates.at(i));
	}
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
	case WHITE:
		glColor3f(1, 1, 1);
		break;
	}
}

void WhitekastObject::draw() {
	setDrawingColor();
	int sizeVariable = 4;
	float scale = sizeVariable / CAMERA_HEIGHT;
	if (objectColor == WHITE) {
		float backgroundY = -0.11f;
		glBegin(GL_QUADS);
			glVertex3f(0, backgroundY, 0);
			glVertex3f(CAMERA_WIDTH * scale, backgroundY, 0);
			glVertex3f(CAMERA_WIDTH * scale, backgroundY, sizeVariable);
			glVertex3f(0, backgroundY, sizeVariable);
		glEnd();
	}
	else {
		float minObjectY = -0.1f;
		float maxObjectY = minObjectY + 0.05f * sizeVariable;
		glBegin(GL_TRIANGLE_STRIP);
			for (int i = 0; i < coordinates.size() - 1; i++) {
				glVertex3f(coordinates[i].x * scale, maxObjectY, coordinates[i].y * scale);
				glVertex3f(coordinates[i + 1].x * scale, maxObjectY, coordinates[i + 1].y * scale);
				glVertex3f(center.x * scale, maxObjectY, center.y * scale);
			}
			float lastX = coordinates[coordinates.size() - 1].x * scale;
			float lastY = coordinates[coordinates.size() - 1].y * scale;
			glVertex3f(lastX, maxObjectY, lastY);
			glVertex3f(coordinates[0].x * scale, maxObjectY, coordinates[0].y * scale);
			glVertex3f(center.x * scale, maxObjectY, center.y * scale);
		glEnd();

		glBegin(GL_QUADS);
			for (int i = 0; i < coordinates.size() - 1; i++) {
				glVertex3f(coordinates[i].x * scale, maxObjectY, coordinates[i].y * scale);
				glVertex3f(coordinates[i + 1].x * scale, maxObjectY, coordinates[i + 1].y * scale);
				glVertex3f(coordinates[i + 1].x * scale, minObjectY, coordinates[i + 1].y * scale);
				glVertex3f(coordinates[i].x * scale, minObjectY, coordinates[i].y * scale);
			}
			glVertex3f(lastX, maxObjectY, lastY);
			glVertex3f(coordinates[0].x * scale, maxObjectY, coordinates[0].y * scale);
			glVertex3f(coordinates[0].x * scale, minObjectY, coordinates[0].y * scale);
			glVertex3f(lastX, minObjectY, lastY);
		glEnd();
	}
}

void WhitekastObject::drawWithTextures()
{
}
