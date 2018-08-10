#include "SoundEngine.h"

ALCenum error;
ALCdevice *device;
ALCcontext *context;
std::vector<Sound*> SoundList;

void check_errors() {
	error = alGetError();
	if (error != AL_NO_ERROR) {
		// something wrong happened
		printf("SoundEngine: ERROR occured at runtime!\n");
	}
}
int TEST_ERROR(const GLchar* _msg) {
	ALCenum error = alGetError();
	if (error != AL_NO_ERROR) {
		fprintf(stderr, _msg);
		printf("\n");
		return -1;
	}
	return 1;
}
void SoundEngine::Initialize() {
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f };
	//DEVICE ENUMERATION
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE) {
		fprintf(stderr, "enumeration extension not available\n");
	}
	else {
		// enumeration supported
	}
	//RETREIVE THE DEVICE LIST
	//list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!device) {
		fprintf(stderr, "unable to open default device\n");
	}
	//ERROR STACK INITIALIZATION AND USAGE
	alGetError();
	//CONTEXT CREATION AND INITIALIZATION
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		// failed to make context current
		check_errors();
	}
	/* set orientation */
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	TEST_ERROR("listener position");
	alListener3f(AL_VELOCITY, 0, 0, 0);
	TEST_ERROR("listener velocity");
	alListenerfv(AL_ORIENTATION, listenerOri);
	TEST_ERROR("listener orientation");
}
void SoundEngine::Revert() {
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		printf("Deallocating memory from original sound: %s\n", SoundList[i]->path);
		delete SoundList[i];
	}
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
ALint getFileSize(const ALchar* path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	return file.tellg();
}
void SoundEngine::setListenerPosition(glm::vec3 l_pos) {
	ALfloat listenerOri[] = { l_pos.x, l_pos.y, 1.0f, 0.0f, 0.0f, -1.0f };

	alListener3f(AL_POSITION, l_pos.x, l_pos.y, 1.0f);
	TEST_ERROR("listener position");
	alListenerfv(AL_ORIENTATION, listenerOri);
	TEST_ERROR("listener orientation");
}
Sound* SoundEngine::loadSound(const ALchar* path, WaveFile* data) {
	//Check if file exists
	if (std::ifstream(path)) {
		Sound* wav = new Sound(path, data);
		SoundList.push_back(wav);
		return wav;
	}
	else {
		printf("ERROR: Attempted to load a nonexistant sound ( sound:%s )\n", path);
		printf("ERROR: Undefined behavior expected ( sound:%s )\n", path);
	}
	//Only get here if file doesn't exist.
	return nullptr;
}
Sound* SoundEngine::getOriginalSound(const ALchar* path) {
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		if (SoundList[i]->copy == AL_FALSE && !strcmp(SoundList[i]->path, path)) {
			return SoundList[i];
		}
	}
	printf("ERROR: Attempted to GET a nonexistant sound ( sound:%s )\n", path);
	printf("ERROR: Undefined behavior expected ( sound:%s )\n", path);
	//Only get here if you didn't load the sound.
	return nullptr;
}
void SoundEngine::list_audio_devices(const ALCchar *devices) {
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;
	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}
void SoundEngine::playSound(const ALchar* path, glm::vec2 pos, ALboolean loop) {
	bool sound_exists = false;
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		if (!strcmp(path, SoundList[i]->path)) {
			loadSound(SoundList[i]->path, SoundList[i]->Wave);
			SoundList[SoundList.size() - 1]->setPos(pos);
			SoundList[SoundList.size() - 1]->setLoop(loop);
			alSourcePlay(SoundList[SoundList.size()-1]->source);
			sound_exists = true;
			break;
		}
	}
	if (!sound_exists) {
		Sound* sound = loadSound(path, nullptr);
		playSound(sound->path, pos, loop);
	}
}
void SoundEngine::pauseSound(const ALchar* path) {
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		if (strcmp(path, SoundList[i]->path) == 0) {
			ALenum source_state = 0;
			alGetSourcei(SoundList[i]->source, AL_SOURCE_STATE, &source_state);
			if (source_state == AL_PLAYING) {
				alSourcePause(SoundList[i]->source);
				break;
			}
		}
	}
}
void SoundEngine::stopSound(const ALchar* path) {
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		if (strcmp(path, SoundList[i]->path) == 0) {
			ALenum source_state = 0;
			alGetSourcei(SoundList[i]->source, AL_SOURCE_STATE, &source_state);
			if (source_state == AL_PLAYING) {
				alSourceStop(SoundList[i]->source);
				break;
			}
		}
	}
}
void SoundEngine::Refresh() {
	for (unsigned int i = 0; i < SoundList.size(); i++) {
		ALenum source_state = 0;
		alGetSourcei(SoundList[i]->source, AL_SOURCE_STATE, &source_state);
		if(source_state != AL_PLAYING && SoundList[i]->copy == AL_TRUE) {
			printf("Deallocating memory from sound copy: %s\n", SoundList[i]->path);
			delete SoundList[i];
			SoundList.erase(SoundList.begin() + i);
		}
	}
}