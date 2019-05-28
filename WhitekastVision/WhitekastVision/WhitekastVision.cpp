#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "WhitekastObject.h"
#include <iostream>
#include <string>
#include "WhitekastVision.h"
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;
using namespace std::this_thread; 
using namespace std::chrono;

const int minMotion = -15000;

Mat redFrame, greenFrame, blueFrame;
vector<WhitekastObject> redObjects, greenObjects, blueObjects;
VideoCapture vCap(1);
bool movingLeft;
bool movingRight;
Ptr<SimpleBlobDetector> detector;

int main()
{
	if (!vCap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		exit(0);
	}

	int running = 1;
	while (running) {
		running = captureFrames();
	}

	findObjectsByFrame(redFrame, &redObjects, RED);
	findObjectsByFrame(greenFrame, &greenObjects, GREEN);
	findObjectsByFrame(blueFrame, &blueObjects, BLUE);

	waitKey(0);
	SimpleBlobDetector::Params params;
	// Change thresholds
	params.minArea = 10;
	params.filterByArea = true;
	detector = SimpleBlobDetector::create(params);
	running = 1;
	while (running)
	{
		captureMovement();
		cout << movingRight;
	}
	
	waitKey(0);

	return 0;
}

//This method is checking any motion 
int captureMovement() {
	Mat videoFrame, videoFrame2;
	vCap.read(videoFrame);
	cvtColor(videoFrame, videoFrame, COLOR_BGR2GRAY);
	imshow("move1", videoFrame);
	threshold(videoFrame, videoFrame, 100, 255, THRESH_BINARY_INV);
	imshow("move1", videoFrame);

	vCap.read(videoFrame2);
	cvtColor(videoFrame2, videoFrame2, COLOR_BGR2GRAY);
	threshold(videoFrame2, videoFrame2, 100, 255, THRESH_BINARY_INV);
	imshow("move2", videoFrame2);
	

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
int getWhitePixelsLeft(Mat mat)
{
	int count = 0;
	for (int x = 0; x < mat.rows; x++)
	{
		for (int y = 0; y < mat.cols/2; y++)
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
int getWhitePixelsRight(Mat mat)
{
	int count = 0;
	for (int x = 0; x < mat.rows; x++)
	{
		for (int y = mat.cols/2; y < mat.cols; y++)
		{
			if (mat.at<uchar>(x, y) == 255)
			{
				count++;
			}
		}
	}
	return count;
}

int captureFrames() {
	Mat videoFrame;
	vCap.read(videoFrame);

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

	imshow("Red", redFrame);
	imshow("Green", greenFrame);
	imshow("Blue", blueFrame);

	if (waitKey(1) == 27) {
		return 0;
	}
	return 1;
}

void findObjectsByFrame(Mat frame, vector<WhitekastObject>* objects, ObjectColor objectColor) {
	threshold(frame, frame, 100, 255, 0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(frame, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Mat contourFrame = Mat::zeros(frame.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		double areaContour = contourArea(contours[i]);
		if (areaContour > 500.0) {
			Scalar color = Scalar(0, 255, 255);
			drawContours(contourFrame, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

			WhitekastObject object = WhitekastObject(objectColor);
			object.setCoordinates(contours[i]);
			objects->push_back(object);
		}
	}

	imshow("contour" + objectColor, contourFrame);
}
