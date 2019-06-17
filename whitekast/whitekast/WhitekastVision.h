/*
	WhitekastVision
	Purpose: Opperating the camera for vision mechanics.

	@version 1.2 - 2019/06/03
*/

#pragma once
#ifndef DEFINITIONS

#define H_MIN_RED 160
#define H_MAX_RED 20

#define H_MIN_GREEN 35
#define H_MAX_GREEN 75

#define H_MIN_BLUE 100
#define H_MAX_BLUE 140

#define S_MIN 120
#define S_MAX 255

#define V_MIN 60
#define V_MAX 230

#define CAMERA_WIDTH 640.0f
#define CAMERA_HEIGHT 480.0f

#endif

#include <opencv2/opencv.hpp>
#include <vector>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "WhitekastObject.h"


class WhitekastVision
{
public:	
	WhitekastVision();
	~WhitekastVision();

	/*
		Initializes the vision project, returning all existing whitekast objects.

		@param -
		@return All existing whitekast objects.
	*/
	std::vector<WhitekastObject*> initVision();

	/*
		Starts the computer vision thread.

		@param -
		@return void.
	*/
	void startThread();

	/*
		Captures movement with the camera.

		@param -
		@return int.
	*/
	int captureMovement();

	/*
		Returns the amount of pixels of the left hand.

		@param const cv::Mat mat - The original image capture from the camera.
		@return int.
	*/
	int getWhitePixelsLeft(const cv::Mat mat);

	/*
		Returns the amount of pixels of the right hand.

		@param const cv::Mat mat - The original image capture from the camera.
		@return int.
	*/
	int getWhitePixelsRight(const cv::Mat mat);

	/*
		Returns if the left hand moved.

		@param -
		@return bool.
	*/
	bool getMotionLeft();

	/*
		Returns if the right hand moved.

		@param -
		@return bool.
	*/
	bool getMotionRight();

	/*
		Scans snapshot from the camera for colored objects (enum: red, green, blue or white).

		@param -
		@return The co�rdinates of the whitekast object.
	*/
	int captureFrames();

	/*
		Creates the border according to the camera size.

		@param -
		@return void.
	*/
	void createBorder();

	/*
		Converts the objects found in a picture frame to a whitekast object and adds them
		the whitekast object collection.

		@param Mat frame - The corresponding picture frame.
		@param ObjectColor objectColor - Color of the picture frame.
		@return void.
	*/
	void findObjectsByFrame(const cv::Mat frame, const ObjectColor objectColor);
};
