#pragma once
#include <iostream>
#include <map>

class AudioManager
{

private: 
	AudioManager();

public:
	~AudioManager();
	static AudioManager* getAudioManager();
	void playSound(const char* name);
	void playMusic(const char* name);
};

