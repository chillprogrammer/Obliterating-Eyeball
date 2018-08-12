#include "Player.h"
#include "ResourceManager.h"
Player::Player(const char* img) : Entity(img) {
	angle = 0.0f;
	sound_test = GL_FALSE;
	//thruster_sound = 
}
Player::~Player() {
	//printf("Testing Destruction of SHIP\n");
}
void Player::render() {
	//printf("Testing render SHIP\n");
	if (sound_test) {
		//SoundEngine::playSound("boop", pos);
		SoundEngine::playSound("sounds/blaster.wav", pos, false);
		sound_test = GL_FALSE;
	}
}