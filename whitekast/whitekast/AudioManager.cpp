#include "AudioManager.h"
#include <irrKlang.h>
#include <map>
#include <iostream>

#pragma comment(lib, "irrKlang.lib") //link with irrKlang.dll


static AudioManager* instance;

irrklang::ISoundEngine* engine;
irrklang::ISound* music;
std::map<const char*, irrklang::ISound*> audioMap;

AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	engine->drop();
	for (auto pair : audioMap)
	{
		pair.second->drop();
	}
	delete engine;
	delete music;

}

AudioManager* AudioManager::getAudioManager()
{
	if (instance == NULL)
	{
		instance = new AudioManager();
	}
	return instance;
}

void AudioManager::playSound(const char* name)
{
	if (audioMap.count(name) >= 1)
	{
		engine->play2D(name, false, false, true);
	}
	else 
	{
		irrklang::ISound* sound = engine->play2D(name, false, false, true);
		audioMap.insert(std::pair<const char*, irrklang::ISound*>(name, sound));
	}
}
void AudioManager::playMusic(const char * name)
{
	if (music == NULL)
	{
		music = engine->play2D(name, true, false, true);
	}
	else
	{
		music->drop();
		music = NULL;
		music = engine->play2D(name, true, false, true);
	}
}




