#pragma once
#include <irrKlang.h>
#include <iostream>
#include <map>

class AudioManager
{

private: 
	AudioManager();

public:
	~AudioManager();
	static AudioManager* getInstance();
	void playSound(const char* name);
	void playMusic(const char* name);
};

