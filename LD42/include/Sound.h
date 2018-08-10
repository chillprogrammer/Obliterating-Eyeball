#ifndef SOUND_H
#define SOUND_H
#include "WaveFile.h"
#include "al.h" 
#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

struct Sound {
	Sound(const ALchar* caller, WaveFile* original);
		//If original is set to nullptr, then the filereader will read the wave file.
		//If sound is a copy, then pass 'original' with the original Sound->Wave pointer;
	~Sound();
	void setPos(glm::vec2 pos);
	void setVel(glm::vec2 vel);
	void setLoop(ALboolean loop);
	void setPitch(ALfloat pitch);
	void setVolume(ALfloat pitch);
	WaveFile* Wave;
	ALuint source;
	ALuint buffer;
	ALchar* path;
	ALboolean copy;
};
#endif
