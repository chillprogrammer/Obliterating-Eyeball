#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdlib.h>

class Camera {
public:
	static void setMat4(glm::mat4);
	static void translateMatrix(glm::vec3);
	static void translateCamera(glm::vec3);
	static void setPosition(glm::vec3);
	static void rotateMatrix(GLfloat);
	static void setSpeed(GLfloat);
	static void resetMatrix();
	static void zoom(GLfloat);	//Positive float zooms in
	static glm::vec2 getFustrum();

	static glm::mat4 Projection;
	static GLfloat Speed, Delta, DEFAULT_SPEED;
	static GLboolean PLAYER_LOCK;
	static GLfloat zoom_amount;
	static glm::vec2 camera_pos;
};
#endif
