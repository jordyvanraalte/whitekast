#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include "DrawComponent.h"

using namespace cv;

enum ObjectColor { RED, GREEN, BLUE, WHITE };

class WhitekastObject : public DrawComponent {
	ObjectColor objectColor;
	std::vector<Point> coordinates;
	Point center;
public:
	WhitekastObject(ObjectColor color);
	~WhitekastObject(void);

	std::vector<Point> getCoordinates();
	void setCoordinates(std::vector<Point> newCoordinates);

	Point getCenter();
	void setCenter(Point centerPoint);

	ObjectColor getObjectColor();
	void setObjectColor(ObjectColor color);

	void setDrawingColor();

	virtual void draw();
};