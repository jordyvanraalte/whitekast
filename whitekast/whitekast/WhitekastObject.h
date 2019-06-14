#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include "DrawComponent.h"
#include "CollideComponent.h"

//using namespace cv;

enum ObjectColor { RED, GREEN, BLUE, WHITE };

class WhitekastObject : public DrawComponent{
	ObjectColor objectColor;
	std::vector<cv::Point> coordinates;
	cv::Point center;
public:
	WhitekastObject(ObjectColor color);
	~WhitekastObject(void);

	std::vector<cv::Point> getCoordinates();
	void setCoordinates(std::vector<cv::Point> newCoordinates);

	cv::Point getCenter();
	void setCenter(cv::Point centerPoint);

	float getScale();

	ObjectColor getObjectColor();
	void setObjectColor(ObjectColor color);

	void setDrawingColor();
	float getSize();
	float getWidth();

	virtual void draw() override;
};
