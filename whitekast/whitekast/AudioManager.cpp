#include "AudioManager.h"
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib") //link with irrKlang.dll

irrklang::ISoundEngine* engine;
irrklang::ISound* backgroundMusic;

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}

void AudioManager::test()
{
	backgroundMusic = engine->play2D("test.mpeg", true, false, true);
}

