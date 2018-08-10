#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include "TextRenderer.h"
#include <GLFW/glfw3.h>
#include "InputManager.h"

struct TextBox
{
	std::string Text;
	std::string default_text;
	GLboolean Clicked;
	GLboolean Visible;
	glm::vec3 backColor;
	glm::vec3 borderColor;
	glm::vec3 textColor;
	GLfloat posx, posy, boxscalex, boxscaley, textscalex, textscaley, border_x, border_y;
	TextBox();
	TextBox(const GLchar* text);
	~TextBox();
	void keyPress(GLint key);
	void render();

	TextRenderer *Text_Renderer;
};
#endif
