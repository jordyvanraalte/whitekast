#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

using namespace cv;

enum ObjectColor {RED, GREEN, BLUE};

class WhitekastObject {
public:
	ObjectColor objectColor;
	std::vector<Point> coordinates;

	WhitekastObject(ObjectColor color);
	~WhitekastObject(void);

	std::vector<Point> getCoordinates();
	//void setCoordinates(std::vector<Point> newCoordinates);

	ObjectColor getObjectColor();
	void setObjectColor(ObjectColor color);
};