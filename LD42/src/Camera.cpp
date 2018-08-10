#include "Camera.h"

glm::mat4 Camera::Projection = glm::mat4(1);
GLfloat Camera::DEFAULT_SPEED = 0.5f;
GLfloat Camera::Speed = DEFAULT_SPEED;
GLfloat Camera::Delta = 0.0f;
GLboolean Camera::PLAYER_LOCK = GL_FALSE;
GLfloat Camera::zoom_amount = 1.0f;
glm::vec2 Camera::camera_pos = glm::vec2(0.0f, 0.0f);

void Camera::setMat4(glm::mat4 mat) {
	Projection = mat;
}
void Camera::resetMatrix() {
	Projection = glm::mat4(1);
	zoom_amount = 1.0f;
}
void Camera::translateMatrix(glm::vec3 v) {
	Projection = glm::translate(Projection, v*Delta);
}
void Camera::setPosition(glm::vec3 v) {
	v.y += 0.5f;
	Projection = glm::mat4(1);
	Projection = glm::scale(Projection, glm::vec3(zoom_amount, zoom_amount, 1.0f));
	Projection = glm::translate(Projection, -v);

	camera_pos = glm::vec2(v.x, v.y);
}
void Camera::rotateMatrix(GLfloat rot) {
	Projection = glm::rotate(Projection, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
}
void Camera::setSpeed(GLfloat s) {
	Speed = s;
}
glm::vec2 Camera::getFustrum() {
	return glm::vec2(Projection[3][0], Projection[3][1]);
}
void Camera::zoom(GLfloat val) {
	zoom_amount *= val;
	Projection = glm::scale(Projection, glm::vec3(val, val, 1.0f));
}