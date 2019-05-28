#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "WhitekastObject.h"
#include <iostream>
#include <string>
#include "WhitekastVision.h"

using namespace cv;
using namespace std;

Mat redFrame, greenFrame, blueFrame;
vector<WhitekastObject*> visionObjects;
VideoCapture vCap(0);

vector<WhitekastObject*> initVision()
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

	waitKey(0);

	createBorder();
	findObjectsByFrame(redFrame, RED);
	findObjectsByFrame(greenFrame, GREEN);
	findObjectsByFrame(blueFrame, BLUE);

	return visionObjects;
}

int captureFrames() {
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

void createBorder()
{
	WhitekastObject* object = new WhitekastObject(WHITE);
	double cx = CAMERA_WIDTH / 2.0;
	double cy = CAMERA_HEIGHT / 2.0;
	Point centerPoint = Point(cx, cy);
	object->setCenter(centerPoint);
	visionObjects.push_back(object);
}

void findObjectsByFrame(const Mat frame, const ObjectColor objectColor) {
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
			object->setCoordinates(contours[i]);
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
