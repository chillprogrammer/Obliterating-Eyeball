#include "Eye.h"
#include "ResourceManager.h"

Eye::Eye(const char* img_path) : Entity(img_path) {
	if (ResourceManager::getShaderID("Eyeball") == 0)
		ResourceManager::loadShader("shaders/Eyeball.vs", "shaders/Eyeball.fs", "Eyeball");
	health = 100.0f;
	pos.x = 1.5f;
	pos.y = 2.0f;
	scale.x = 0.2f;
	scale.y = 0.15*1.777f;
	shader_caller = "Eyeball";
	pupil_pos = glm::vec2(0.5f, 0.5f);
	pupil_scale = glm::vec2(0.15f, 0.2f);
	//velocity.x = 0.1f;
	//velocity.y = -0.1f;
}
Eye::~Eye() {

}
void Eye::updateEye(float d) {

}
void Eye::render() {

}