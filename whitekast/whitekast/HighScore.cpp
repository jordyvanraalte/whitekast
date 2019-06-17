#include <iostream>
#include <fstream>
#include <string>

#include "HighScore.h"

HighScore* highScoreInstance;
std::string fileName = "highscore.txt";

HighScore::HighScore()
{
	
}

HighScore::~HighScore()
{
	delete highScoreInstance;
}

 int HighScore::getHighScore()
{
	std::ifstream in(fileName.c_str());
	std::string highScore = "-1";

	if (!in)
	{
		std::cout << "Can't open the file : " << fileName << std::endl;
		return -1;
	}

	std::getline(in, highScore);

	in.close();

	return std::atoi(highScore.c_str());
}

void HighScore::setHighScore(int highScore)
{
	if (getHighScore() > highScore)
		return;

	std::ofstream out;
	out.open(fileName);

	if (!out)
	{
		std::cerr << "Can't open the file : " << fileName << std::endl;
		return;
	}
	
	out << highScore << std::endl;

	out.close();
}

HighScore* HighScore::getInstance()
{
	if (highScoreInstance == nullptr)
		highScoreInstance = new HighScore();

	return highScoreInstance;
}
