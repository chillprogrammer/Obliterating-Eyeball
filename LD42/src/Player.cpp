#include "Player.h"
#include "ResourceManager.h"
Player::Player(const char* img) : Entity(img) {
	thrust_force = 0.5f;
	turn_force = 85.0f;
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