#include "Sound.h"
#include "Camera.h"
ALchar* ReadAllBytes(const char * filename, int * read) {
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();
	ALsizei length = pos;
	ALchar *pChars = new char[length];
	ifs.seekg(0, std::ios::beg);
	ifs.read(pChars, length);
	ifs.close();
	*read = length;
	return pChars;
}
inline ALenum to_al_format(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}
Sound::Sound(const ALchar* file_path, WaveFile* original) {
	path = _strdup(file_path);
	alGenSources((ALuint)1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 0.5);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
	alGenBuffers(1, &buffer);
	ALsizei len;
	if (original == nullptr) {
		Wave = (WAV_HEADER*)ReadAllBytes(path, &len);
		copy = AL_FALSE;
	}
	else {
		Wave = original;
		copy = AL_TRUE;
	}
	alBufferData(buffer, to_al_format(Wave->NumberOfChanels, Wave->BitsPerSecond),
		Wave->data, Wave->SubChunk2Size, Wave->SampleRate);
	alSourcei(source, AL_BUFFER, buffer);
}
Sound::~Sound() {
	if(copy == AL_FALSE)
		delete Wave;
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	free(path);
}
void Sound::setPos(glm::vec2 pos) {
	alSource3f(source, AL_POSITION, pos.x-Camera::camera_pos.x, pos.y - Camera::camera_pos.y, -1.0f);
}
void Sound::setVel(glm::vec2 vel) {
	alSource3f(source, AL_VELOCITY, vel.x, vel.y, 0);
}
void Sound::setLoop(ALboolean loop) {
	alSourcei(source, AL_LOOPING, loop);
}
void Sound::setVolume(ALfloat gain) {
	alSourcef(source, AL_GAIN, gain);
}
void Sound::setPitch(ALfloat pitch) {
	alSourcef(source, AL_PITCH, pitch);
}