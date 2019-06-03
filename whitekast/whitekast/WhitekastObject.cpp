#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "DrawComponent.h"
#include "GL/freeglut.h"

std::vector<cv::Point> coordinates;
cv::Point center;
ObjectColor objectColor;
int size = 4;
float widthBoard;
float scale = size / CAMERA_HEIGHT;

WhitekastObject::WhitekastObject(ObjectColor color) {
	
	objectColor = color;
	widthBoard = scale * CAMERA_WIDTH;
}

WhitekastObject::~WhitekastObject() {}

std::vector<cv::Point> WhitekastObject::getCoordinates()
{
	return coordinates;
}

void WhitekastObject::setCoordinates(std::vector<cv::Point> newCoordinates)
{
	//coordinates = newCoordinates;
	for (int i = 0; i < newCoordinates.size(); i += 2) {
		coordinates.push_back(newCoordinates.at(i));
	}
}

cv::Point WhitekastObject::getCenter()
{
	return center;
}

void WhitekastObject::setCenter(cv::Point centerPoint)
{
	center = centerPoint;
}

float WhitekastObject::getScale()
{
	return scale;
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

float WhitekastObject::getSize()
{
	return size;
}

void WhitekastObject::draw() 
{
	setDrawingColor();
	if (objectColor == WHITE) {
		float backgroundY = -2.01f;

		glBegin(GL_QUADS);

		glVertex3f(0, backgroundY, 0);
		glVertex3f(CAMERA_WIDTH * scale, backgroundY, 0);
		glVertex3f(CAMERA_WIDTH * scale, backgroundY, size);
		glVertex3f(0, backgroundY, size);

		glVertex3f(0, -2, 0);
		glVertex3f(0, -2, size);
		glVertex3f(0, -10, size);
		glVertex3f(0, -10, 0);

		glVertex3f(widthBoard, -2, 0);
		glVertex3f(widthBoard, -2, size);
		glVertex3f(widthBoard, -10, size);
		glVertex3f(widthBoard, -10, 0);

		glVertex3f(0, -2, size);
		glVertex3f(widthBoard, -2, size);
		glVertex3f(widthBoard, -10, size);
		glVertex3f(0, -10, size);

		glEnd();
		glColor3f(1, 1, 1);
	}
	else 
	{
		float minObjectY = -2.0f;
		float maxObjectY = minObjectY + 0.05f * size;
		//glTranslatef(size / 5, 0, widthBoard);
		//glScalef(1, 1, -1);


		glBegin(GL_TRIANGLE_STRIP);
			for (int i = 0; i < coordinates.size() - 1; i++) 
			{
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
			for (int i = 0; i < coordinates.size() - 1; i++) 
			{
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
		//glTranslatef(-size / 5, 0, -widthBoard);
		glColor3f(1, 1, 1);
	}
}

