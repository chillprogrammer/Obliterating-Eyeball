#ifndef BUTTON_H
#define BUTTON_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include "TextRenderer.h"
#include "InputManager.h"

class Button
{
public:
	TextRenderer *Text_Renderer;
	std::string Text;
	std::string Shortcut;
	GLboolean Clicked, Visible, context_button, is_active;
	glm::vec3 backColor;
	glm::vec3 borderColor;
	glm::vec3 hoverColor;
	glm::vec3 textColor;
	GLfloat posx, posy, scalex, scaley, border_x, border_y;
	Button();
	Button(const GLchar* text, const GLchar* shortcut);
	Button(const GLchar* text);
	~Button();
	void render();
};
#endif