#include "Audio.h"

Audio* Audio::instance = nullptr;

Audio* Audio::makeInstance()
{
	if (instance == nullptr) {
		instance = new Audio();
	}
	return instance;;
}

Mix_Chunk* Audio::getChunk(std::string filepath)
{
	return Mix_LoadWAV(filepath.c_str());
}

void Audio::Release()
{
	delete instance;
	instance = nullptr;
}

void Audio::playMusic(Mix_Music* music, int loops)
{
	Mix_PlayMusic(music, loops);
}

void Audio::pauseMusic()
{
	if (Mix_PlayingMusic() != 0) {
		Mix_PauseMusic();
	}
}

void Audio::resumeMusic()
{
	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void Audio::playEffect(Mix_Chunk* effect, int loops, int channel)
{
	Mix_PlayChannel(channel, effect, loops);
}
