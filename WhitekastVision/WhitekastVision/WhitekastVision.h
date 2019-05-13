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
#endif

int captureFrames();
void findObjectsByFrame(Mat, std::vector<WhitekastObject>*, ObjectColor);
