#include "WhitekastObject.h"
#include <iostream>
#include <string>
#include "WhitekastVision.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <atomic>

using namespace cv;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

Mat redFrame, greenFrame, blueFrame;
vector<WhitekastObject*> visionObjects;
VideoCapture vCap(0);

std::atomic<bool> movingLeft;
std::atomic<bool> movingRight;
const int minMotion = -15000;

WhitekastVision::WhitekastVision()
{
}

WhitekastVision::~WhitekastVision()
{
}

vector<WhitekastObject*> WhitekastVision::initVision()
{
	if (!vCap.isOpened())
	{
		std::cout << "Cannot open the video cam" << std::endl;
		exit(0);
	}
	double dWidth = vCap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = vCap.get(CV_CAP_PROP_FRAME_HEIGHT);
	std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

	int running = 1;
	while (running) {
		running = captureFrames();
	}

	createBorder();
	findObjectsByFrame(redFrame, RED);
	findObjectsByFrame(greenFrame, GREEN);
	findObjectsByFrame(blueFrame, BLUE);

	return visionObjects;
}

void WhitekastVision::startThread()
{
	while (1)
	{
		captureMovement();
	}
}

int WhitekastVision::captureMovement()
{
	Mat videoFrame, videoFrame2;
	vCap.read(videoFrame);
	cvtColor(videoFrame, videoFrame, COLOR_BGR2GRAY);
	//imshow("move1", videoFrame);
	threshold(videoFrame, videoFrame, 100, 255, THRESH_BINARY_INV);
	//imshow("move1", videoFrame);

	vCap.read(videoFrame2);
	cvtColor(videoFrame2, videoFrame2, COLOR_BGR2GRAY);
	threshold(videoFrame2, videoFrame2, 100, 255, THRESH_BINARY_INV);
	//imshow("move2", videoFrame2);


	if (getWhitePixelsLeft(videoFrame) - getWhitePixelsLeft(videoFrame2) <= minMotion)
	{
		movingLeft = true;
	}
	else
	{
		movingLeft = false;
	}

	if (getWhitePixelsRight(videoFrame) - getWhitePixelsRight(videoFrame2) <= minMotion)
	{
		movingRight = true;
	}
	else
	{
		movingRight = false;
	}

	if (waitKey(1) == 27) {
		return 0;
	}

	return 1;
}

//This method will return the count of white pixels on the left side of the picture(mat) 
int WhitekastVision::getWhitePixelsLeft(const Mat mat)
{
	int count = 0;
	for (int x = 0; x < mat.rows; x++)
	{
		for (int y = 0; y < mat.cols / 2; y++)
		{
			if (mat.at<uchar>(x, y) == 255)
			{
				count++;
			}
		}
	}
	return count;
}

//This method returns the count of white pixels on the right side of the picture(mat) 
int WhitekastVision::getWhitePixelsRight(const Mat mat)
{
	int count = 0;
	for (int x = 0; x < mat.rows; x++)
	{
		for (int y = mat.cols / 2; y < mat.cols; y++)
		{
			if (mat.at<uchar>(x, y) == 255)
			{
				count++;
			}
		}
	}
	return count;
}

bool WhitekastVision::getMotionLeft()
{
	return movingLeft;
}

bool WhitekastVision::getMotionRight()
{
	return movingRight;
}

int WhitekastVision::captureFrames() 
{
	Mat videoFrame;
	vCap.read(videoFrame);

	imshow("Whitekast Level Setup", videoFrame);

	Mat hsvFrame;
	cvtColor(videoFrame, hsvFrame, COLOR_BGR2HSV);

	Mat structuringElement = getStructuringElement(MORPH_RECT, Size(6, 6), Point(0, 0));

	Mat redFrame1, redFrame2, redDilation;
	inRange(hsvFrame, Scalar(H_MIN_RED, S_MIN, V_MIN), Scalar(180, S_MAX, V_MAX), redFrame1);
	inRange(hsvFrame, Scalar(0, S_MIN, V_MIN), Scalar(H_MAX_RED, S_MAX, V_MAX), redFrame2);

	redFrame = redFrame1 | redFrame2;
	dilate(redFrame, redDilation, structuringElement);
	erode(redDilation, redFrame, structuringElement);

	inRange(hsvFrame, Scalar(H_MIN_GREEN, S_MIN, V_MIN), Scalar(H_MAX_GREEN, S_MAX, V_MAX), greenFrame);
	Mat greenDilation;
	dilate(greenFrame, greenDilation, structuringElement);
	erode(greenDilation, greenFrame, structuringElement);

	inRange(hsvFrame, Scalar(H_MIN_BLUE, S_MIN, V_MIN), Scalar(H_MAX_BLUE, S_MAX, V_MAX), blueFrame);
	Mat blueDilation;
	dilate(blueFrame, blueDilation, structuringElement);
	erode(blueDilation, blueFrame, structuringElement);
	/*
		imshow("Red", redFrame);
		imshow("Green", greenFrame);
		imshow("Blue", blueFrame);
	*/
	if (waitKey(1) == 27) {
		return 0;
	}
	return 1;
}

void WhitekastVision::createBorder()
{
	WhitekastObject* object = new WhitekastObject(WHITE);
	visionObjects.push_back(object);

	WhitekastObject* bottomLeftWall = new WhitekastObject(GREEN);
	WhitekastObject* leftWall = new WhitekastObject(GREEN);
	WhitekastObject* topWall = new WhitekastObject(GREEN);
	WhitekastObject* rightWall = new WhitekastObject(GREEN);
	WhitekastObject* bottomRightWall = new WhitekastObject(GREEN);
	vector<Point> coordinates1, coordinates2, coordinates3, coordinates4, coordinates5;

	coordinates1.push_back(Point(0.0f, (3.5f*CAMERA_HEIGHT) / 10.0f));
	coordinates1.push_back(Point((1.0f*CAMERA_WIDTH) / 7.0f, (3.5f*CAMERA_HEIGHT) / 10.0f));
	coordinates1.push_back(Point((2.0f*CAMERA_WIDTH) / 7.0f, 0.0f));
	coordinates1.push_back(Point(0.0f, 0.0f));
	bottomLeftWall->setCenter(Point((1.0f*CAMERA_WIDTH) / 12.0f, (1.0f*CAMERA_HEIGHT) / 5.0f));
	bottomLeftWall->setCoordinates(coordinates1, false);

	coordinates2.push_back(Point((1.0f*CAMERA_WIDTH) / 6.0f, 0.0f));
	coordinates2.push_back(Point(CAMERA_WIDTH, 0.0f));
	leftWall->setCoordinates(coordinates2, false);

	coordinates3.push_back(Point(CAMERA_WIDTH, 0.0f));
	coordinates3.push_back(Point(CAMERA_WIDTH, CAMERA_HEIGHT));
	topWall->setCoordinates(coordinates3, false);

	coordinates4.push_back(Point(CAMERA_WIDTH, CAMERA_HEIGHT));
	coordinates4.push_back(Point((1.0f*CAMERA_WIDTH) / 6.0f, CAMERA_HEIGHT));
	rightWall->setCoordinates(coordinates4, false);

	coordinates5.push_back(Point((2.0f*CAMERA_WIDTH) / 7.0f, CAMERA_HEIGHT));
	coordinates5.push_back(Point(0.0f, CAMERA_HEIGHT));
	coordinates5.push_back(Point(0.0f, (6.5f*CAMERA_HEIGHT) / 10.0f));
	coordinates5.push_back(Point((1.0f*CAMERA_WIDTH) / 7.0f, (6.5f*CAMERA_HEIGHT) / 10.0f));
	bottomRightWall->setCenter(Point((1.0f*CAMERA_WIDTH) / 12.0f, (4.0f*CAMERA_HEIGHT) / 5.0f));
	bottomRightWall->setCoordinates(coordinates5, false);

	visionObjects.push_back(bottomLeftWall);
	visionObjects.push_back(leftWall);
	visionObjects.push_back(topWall);
	visionObjects.push_back(rightWall);
	visionObjects.push_back(bottomRightWall);
}

void WhitekastVision::findObjectsByFrame(const Mat frame, const ObjectColor objectColor) 
{
	threshold(frame, frame, 100, 255, 0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(frame, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Mat contourFrame = Mat::zeros(frame.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		double areaContour = contourArea(contours[i]);
		if (areaContour > 500.0) {
			//Scalar color = Scalar(0, 255, 255);
			//drawContours(contourFrame, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

			WhitekastObject* object = new WhitekastObject(objectColor);
			object->setCoordinates(contours[i], true);
			Rect rect = boundingRect(contours[i]);
			double cx = rect.x + rect.width / 2.0;
			double cy = rect.y + rect.height / 2.0;
			Point centerPoint = Point(cx, cy);
			object->setCenter(centerPoint);
			visionObjects.push_back(object);
		}
	}

	//imshow("contour" + objectColor, contourFrame);
}
