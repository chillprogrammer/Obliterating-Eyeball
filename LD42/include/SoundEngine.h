#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "al.h" 
#include "alc.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Sound.h"
#include <vector>
#include <glm/glm.hpp>

struct SoundEngine {
	static void Initialize();
	static void Revert();
	static void Refresh();
	static void setListenerPosition(glm::vec3);
	static Sound* loadSound(const ALchar* path, WaveFile* data);	//If sound is new, leave data nullptr.
	//static inline ALenum to_al_format(short channels, short samples);
	static Sound* getOriginalSound(const ALchar* path);
	static void playSound(const ALchar* path, glm::vec2 pos, ALboolean loop);
	static void pauseSound(const ALchar* path);
	static void stopSound(const ALchar* path);
	static void list_audio_devices(const ALCchar *devices);
};
#endif