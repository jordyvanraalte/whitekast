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

	hitbox = new LinesHitbox(coordinates, scale);
}

cv::Point WhitekastObject::getCenter()
{
	return center;
}

void WhitekastObject::setCenter(cv::Point centerPoint)
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

			//top
			glColor3f(0.3, 0.3, 0.3);
			glVertex3f(0, backgroundY, 0);
			glVertex3f(0, backgroundY, CAMERA_WIDTH * scale);
			glVertex3f(size, backgroundY, CAMERA_WIDTH * scale);
			glVertex3f(size, backgroundY, 0);
		
			//left
			glVertex3f(0, -2, 0);
			glVertex3f(0, -2, widthBoard);
			glVertex3f(0, -10, widthBoard);
			glVertex3f(0, -10, 0);
			
			//right
			glVertex3f(size, -2, 0);
			glVertex3f(size, -2, widthBoard);
			glVertex3f(size, -10, widthBoard);
			glVertex3f(size, -10, 0);

			//front
			glVertex3f(0,-2, widthBoard);
			glVertex3f(size, -2, widthBoard);
			glVertex3f(size, -10, widthBoard);
			glVertex3f(0, -10, widthBoard);

		glEnd();
		glColor3f(1, 1, 1);
	}
	else 
	{
		float minObjectY = -2.0f;
		float maxObjectY = minObjectY + 0.05f * size;
		glTranslatef(size / 5, 0, widthBoard);
		glScalef(1, 1, -1);


		glBegin(GL_TRIANGLE_STRIP);
			for (int i = 0; i < coordinates.size() - 1; i++) 
			{
				glVertex3f(coordinates[i].y * scale, maxObjectY, coordinates[i].x * scale);
				glVertex3f(coordinates[i + 1].y * scale, maxObjectY, coordinates[i + 1].x * scale);
				glVertex3f(center.y * scale, maxObjectY, center.x * scale);
			}
			float lastX = coordinates[coordinates.size() - 1].x * scale;
			float lastY = coordinates[coordinates.size() - 1].y * scale;
			glVertex3f(lastY, maxObjectY, lastX);
			glVertex3f(coordinates[0].y * scale, maxObjectY, coordinates[0].x * scale);
			glVertex3f(center.y * scale, maxObjectY, center.x * scale);
		glEnd();

		glBegin(GL_QUADS);
			for (int i = 0; i < coordinates.size() - 1; i++) 
			{
				glVertex3f(coordinates[i].y * scale, maxObjectY, coordinates[i].x * scale);
				glVertex3f(coordinates[i + 1].y * scale, maxObjectY, coordinates[i + 1].x * scale);
				glVertex3f(coordinates[i + 1].y * scale, minObjectY, coordinates[i + 1].x * scale);
				glVertex3f(coordinates[i].y * scale, minObjectY, coordinates[i].x * scale);
			}
			glVertex3f(lastY, maxObjectY, lastX);
			glVertex3f(coordinates[0].y * scale, maxObjectY, coordinates[0].x * scale);
			glVertex3f(coordinates[0].y * scale, minObjectY, coordinates[0].x * scale);
			glVertex3f(lastY, minObjectY, lastX);
		glEnd();
		glTranslatef(-size / 5, 0, -widthBoard);
		glColor3f(1, 1, 1);
	}
}

Hitbox* WhitekastObject::getHitbox()
{
	return nullptr;
}

