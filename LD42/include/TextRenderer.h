#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <string>

class TextRenderer {
public:
	TextRenderer();
	~TextRenderer();
	void setAppropriateChar(const char ch);
	void render(const std::string text, GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, glm::vec3 color, GLfloat rotation);
private:
	unsigned int VBO, VAO, EBO;
	glm::vec2 tilePosition;
	glm::mat4 projection;
};
#endif