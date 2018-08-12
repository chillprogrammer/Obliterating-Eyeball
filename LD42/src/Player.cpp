#include "Player.h"
#include "ResourceManager.h"
Player::Player(const char* img) : Entity(img) {
	if (ResourceManager::getShaderID("Player") == 0)
		ResourceManager::loadShader("shaders/Player.vs", "shaders/Player.fs", "Player");
	health = 100.0f;
	velocity.y = 0.0f;
	pos.x = 1.51f;
	pos.y = 1.5f;
	scale.x = 0.05f;
	scale.y = 0.1*1.777f;
	shader_caller = "Player";

	//The frame in which to animate
	animation_frame = 0;
	total_animation_frames = 16.0f;
}
Player::~Player() {

}
void Player::updatePlayer(float delta) {
	//Makes sure the entity's velocity responds to gravity
	if (InputManager::State != PAUSED) {
		velocity.y += GRAVITY;
	}
	//Cycles through the animation frames
	static float rate = 0.0f;
	rate += 0.1f;
	if (velocity.x == 0.0f) {
		if (animation_frame < 11)
			animation_frame = 11;
		if (rate > 1.0f) {
			animation_frame++;
			rate = 0.0f;
		}
		if (animation_frame > 15)
			animation_frame = 11;
	}
	else  {
		if (velocity.x > 0.0f) {
			if (scale.x < 0.0f)
				scale.x *= -1;
		}
		else {
			if (scale.x > 0.0f)
				scale.x *= -1;
		}
		if (animation_frame > 8)
			animation_frame = 0;
		if (rate > 1.0f) {
			animation_frame++;
			rate = 0.0f;
		}
	}
}
void Player::render() {

}