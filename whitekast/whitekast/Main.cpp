// whitekast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include <vector>
#include <thread> 


Game *game = nullptr;

void startVisionThread()
{
	game->startVisionThread();
}

int main(int argc, char *argv[]) 
{	
	game = new Game("Whitekast!", argc, argv);
	std::thread visionThread(startVisionThread);
	game->startGame();
	
	return 0;
}
