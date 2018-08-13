#include "Eye.h"
#include "ResourceManager.h"

Eye::Eye(const char* img_path) : Entity(img_path) {
	if (ResourceManager::getShaderID("Eyeball") == 0)
		ResourceManager::loadShader("shaders/Eyeball.vs", "shaders/Eyeball.fs", "Eyeball");
	health = 100.0f;
	pos.x = 1.95f;
	pos.y = 2.0f;
	scale.x = 0.15f;
	scale.y = 0.15*1.777f;
	shader_caller = "Eyeball";
	pupil_pos = glm::vec2(0.5f, 0.5f);
	pupil_scale = glm::vec2(0.15f, 0.15f);
	velocity.y = -0.1f;
	attacking = false;
}
Eye::~Eye() {

}
void Eye::updateEye(float d) {
	if (InputManager::State == PLAYING) {
		fire_counter += 1.0f*d;
		if (fire_counter > 1.0f && attacking == false) {
			attacking = true;
			fire_counter = 0.0f;
			SoundEngine::playSound("sounds/blast.wav", glm::vec2(0.0f, 0.0f), false);
		}
	}
}
void Eye::render() {

}