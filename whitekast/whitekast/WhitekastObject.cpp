#define PLAYINGFIELD_SIZE 4;

#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "DrawComponent.h"
#include "GL/freeglut.h"

std::vector<cv::Point> coordinates;
cv::Point center;
ObjectColor objectColor;

float widthBoard,
	playingfieldSize = PLAYINGFIELD_SIZE;
float scale = playingfieldSize / CAMERA_HEIGHT;


WhitekastObject::WhitekastObject(ObjectColor color)
{
	objectColor = color;
	widthBoard = scale * CAMERA_WIDTH;
}

WhitekastObject::~WhitekastObject() { }

std::vector<cv::Point> WhitekastObject::getCoordinates()
{
	return coordinates;
}

void WhitekastObject::setCoordinates(std::vector<cv::Point> newCoordinates, bool filterCoordinates)
{
	if (filterCoordinates)
	{
		int size = static_cast<int>(newCoordinates.size());
		for (int i = 0; i < size; i += 2)
			coordinates.push_back(newCoordinates.at(i));
	}
	else
		coordinates = newCoordinates;
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
	switch (objectColor)
	{
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
	return PLAYINGFIELD_SIZE;
}

float WhitekastObject::getWidth()
{
	return widthBoard;
}

void WhitekastObject::draw()
{
	setDrawingColor();
	float minObjectY = -2.0f,
		maxObjectY = minObjectY + 0.05f * playingfieldSize;

	if (objectColor == WHITE)
	{
        float backgroundY = -2.0f;

		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_QUADS);

		glVertex3f(-(2.0f * widthBoard) / 7.0f, backgroundY, 0);
		glVertex3f(widthBoard, backgroundY, 0);
		glVertex3f(widthBoard, backgroundY, playingfieldSize);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, backgroundY, playingfieldSize);
		glEnd();

		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -2, 0);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -2, playingfieldSize);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -10, playingfieldSize);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -10, 0);

		glVertex3f(-(2.0f * widthBoard) / 7.0f, -2, playingfieldSize);
		glVertex3f(widthBoard, -2, playingfieldSize);
		glVertex3f(widthBoard, -10, playingfieldSize);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -10, playingfieldSize);

		glVertex3f(-(2.0f * widthBoard) / 7.0f, -2, 0);
		glVertex3f(widthBoard, -2, 0);
		glVertex3f(widthBoard, -10, 0);
		glVertex3f(-(2.0f * widthBoard) / 7.0f, -10, 0);

		glEnd();
	}
	else 
	{
		float lastX = coordinates[coordinates.size() - 1].x * scale,
			lastY = coordinates[coordinates.size() - 1].y * scale;

		if (objectColor == GREEN)
		{
			maxObjectY += 0.05f;
			if (center.x != 0 && center.y != 0)
			{
				glBegin(GL_TRIANGLES);

				int size = static_cast<int>(coordinates.size());
				for (int i = 0; i < (size - 1); i++)
				{
					glVertex3f(coordinates[i].x * scale, maxObjectY, coordinates[i].y * scale);
					glVertex3f(coordinates[i + 1].x * scale, maxObjectY, coordinates[i + 1].y * scale);
					glVertex3f(center.x * scale, maxObjectY, center.y * scale);
				}

				glVertex3f(lastX, maxObjectY, lastY);
				glVertex3f(coordinates[0].x * scale, maxObjectY, coordinates[0].y * scale);
				glVertex3f(center.x * scale, maxObjectY, center.y * scale);

				glEnd();
			}
		}

		

		glBegin(GL_QUADS);

		int size = static_cast<int>(coordinates.size());
		for (int i = 0; i < size - 1; i++)
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

		glColor3f(1, 1, 1);
	}
}
