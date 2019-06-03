/*
	AudioManagar
	Purpose: Plays sounds and music.

	@version 1.3 - 2019/06/03
*/

#pragma once

#include <irrKlang.h>
#include <iostream>
#include <map>

class AudioManager
{
private: 
	irrklang::ISoundEngine* engine;
	irrklang::ISound* music;
	std::map<const char*, irrklang::ISound*> audioMap;

	AudioManager();

public:
	~AudioManager();

	/*
		Returns the instance of the audio manager,
		if it does not exist yet it will be made.
		
		@param -
		@return The instance of the Audio manager.
	*/
	static AudioManager* getInstance();
	
	/*
		Searches for the sound file, 
		if it finds the file it will play the music once.

		@param name -  The name of the file you want to play.
		@return void.
	*/
	void playSound(const char* name);

	/*
		Searches for the sound file, 
		if it finds the file it will play the music in a loop.

		@param name -  The name of the file you want to play.
		@return void.
	*/
	void playMusic(const char* name);
};
