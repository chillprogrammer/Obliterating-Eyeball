#include "Entity.h"
#include "ResourceManager.h"
Entity::Entity(const GLchar* img_path) {
	visible = true;
	angle = 0.0f;
	pos.x = 0.01f;
	pos.y = -0.44f;
	scale.x = 0.06f;
	scale.y = 0.06f;
	velocity.x = 0;
	velocity.y = 0;
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	alpha = 1.0f;
	if (ResourceManager::getTextureID(img_path) == 0)
		ResourceManager::loadTexture(img_path, img_path);
	image = img_path;
}
Entity::~Entity() {
	//printf("Testing Destruction of ENTITY\n");
}
const GLchar* Entity::getImage() {
	return image.c_str();
}
void Entity::setPosition(GLfloat x, GLfloat y) {
	pos.x = x;
	pos.y = y;
}
void Entity::translatePosition(GLfloat x, GLfloat y) {
	pos.x += x;
	pos.y += y;
}
void Entity::setVelocity(GLfloat x, GLfloat y) {
	velocity.x = x;
	velocity.y = y;
}
glm::vec2 Entity::getVelocity() {
	return velocity;
}
void Entity::setAng(GLfloat ang) {
	angle = ang;
}
glm::vec2 Entity::getPos() {
	return pos;
}
glm::vec2 Entity::getScale() {
	return scale;
}
GLfloat Entity::getAng() { return angle; }
GLfloat Entity::getTurnThrust() { return turn_force; }
void Entity::update(GLfloat d) {
	delta = d;
	translatePosition(velocity.x*delta, velocity.y*delta);
}
void Entity::render() {} //Virtual Void