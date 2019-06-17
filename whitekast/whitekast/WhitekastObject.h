/*
	WhitekastObject
	Purpose: The objects that will be drawn in the 3D environment.

	@version 1.4 - 2019/06/03
*/

#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include "DrawComponent.h"
#include "CollideComponent.h"

enum ObjectColor {
	RED, GREEN, BLUE, WHITE
};


class WhitekastObject : public DrawComponent
{
	ObjectColor objectColor;
	std::vector<cv::Point> coordinates;
	cv::Point center;

public:
	WhitekastObject(ObjectColor color);
	~WhitekastObject(void);

	/*
		Returns the coördinates surrounding the whitekast object (the perimeter).

		@param -
		@return The coördinates of the whitekast object.
	*/
	std::vector<cv::Point> getCoordinates();

	/*
		Sets the co�rdinates surrounding the whitekast object (the perimeter)
		to the inserted co�rdinates.

		@param vector<Point> newCoordinates - The new co�rdinates being inserted.
		@param bool filterCoordinates - If these are filter coördinates or not.
		@return void.
	*/
	void setCoordinates(std::vector<cv::Point> newCoordinates, bool filterCoordinates);

	/*
		Returns the center of the whitekast object.

		@param -
		@return The center of the whitekast object.
	*/
	cv::Point getCenter();

	/*
		Sets the center point to the inserted co�rdinates.

		@param Point centerPoint - The new center point being inserted.
		@return void.
	*/
	void setCenter(cv::Point centerPoint);

	/*
		Returns the scale.

		@param -
		@return float.
	*/
	float getScale();

	/*
		Returns the whitekast object's color (enum: red, green, blue or white).

		@param -
		@return The whitekast object's color.
	*/
	ObjectColor getObjectColor();

	/*
		Sets the whitekast object's color (enum: red, green, blue or white).

		@param ObjectColor color - The new whitekast object's color being inserted.
		@return void.
	*/
	void setObjectColor(ObjectColor color);

	/*
		Sets the whitekast object's drawing color according to the object's color (enum: red, blue, green or white).

		@param -
		@return void.
	*/
	void setDrawingColor();

	/*
		Returns playingfield size.

		@param -
		@return The playingfield size.
	*/
	float getSize();

	/*
		Returns playingfield width.

		@param -
		@return The playingfield width.
	*/
	float getWidth();

	virtual void draw() override;
};
