#include "AudioManager.h"


#pragma comment(lib, "irrKlang.lib") //link with irrKlang.dll

static AudioManager* audioManagerInstance;


AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	engine->drop();

	for (auto pair : audioMap)
		pair.second->drop();
	
	if (music != nullptr)
		delete music;
	
	delete engine;
}

AudioManager* AudioManager::getInstance()
{
	if (audioManagerInstance == nullptr)
		audioManagerInstance = new AudioManager();
	
	return audioManagerInstance;
}

void AudioManager::playSound(const char* name)
{
	if (audioMap.count(name) >= 1)
		engine->play2D(name, false, false, true);
	else 
	{
		irrklang::ISoundSource* source = engine->getSoundSource(name, true);
		source->setDefaultVolume(0.25f);
		
		irrklang::ISound* sound = engine->play2D(source, false, false, true);
		audioMap.insert(std::pair<const char*, irrklang::ISound*>(name, sound));
	}
}

void AudioManager::playMusic(const char* name)
{
	if (music == nullptr)
		music = engine->play2D(name, true, false, true);
	else
	{
		music->drop();
		music = nullptr;
		music = engine->play2D(name, true, false, true);
	}
}




