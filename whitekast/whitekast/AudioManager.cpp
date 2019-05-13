#include "AudioManager.h"
#include <irrKlang.h>


#pragma comment(lib, "irrKlang.lib") //link with irrKlang.dll

irrklang::ISoundEngine* engine;
irrklang::ISound* backgroundMusic;

AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
}


AudioManager::~AudioManager()
{
}

void AudioManager::playSound(const char* name)
{
	backgroundMusic = engine->play2D(name, true, false, true);
}

