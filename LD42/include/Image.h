#ifndef IMAGE_H
#define IMAGE_H
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Image {
	Image(const GLchar*, const GLchar* shader_caller);
	~Image();
	char* path;
	GLchar* shader;
	glm::vec2 pos, scale;
	glm::vec3 color;
	GLfloat alpha;
	bool visible, fixed;
};
#endif
