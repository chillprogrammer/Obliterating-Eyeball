#ifndef ENTITY_H
#define ENTITY_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "SoundEngine.h"
#include "Sound.h"

class Entity {
public:
	Entity(const GLchar* img_path);
	virtual ~Entity();
	virtual void render();
	void update(GLfloat delta);
	void setPosition(GLfloat x, GLfloat y);
	void translatePosition(GLfloat x, GLfloat y);
	void setVelocity(GLfloat x, GLfloat y);
	void setAng(GLfloat ang);
	GLfloat getAng();
	glm::vec2 getVelocity();
	glm::vec2 getPos();
	glm::vec2 getScale();
	const GLchar* getImage();
	GLfloat getTurnThrust();
	
	//Public Variables
	GLboolean visible;
	glm::vec3 color;
	GLfloat alpha;
	GLboolean sound_test;
protected:
	glm::vec2 pos, scale, velocity;
	GLfloat delta, angle; //In Degrees
	GLfloat health, thrust_force, turn_force;
	std::string image;
};
#endif