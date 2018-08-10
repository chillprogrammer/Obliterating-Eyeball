#include "Button.h"

Button::Button() : Text("NULL"), Shortcut("NULL"), Clicked(GL_FALSE), Visible(GL_FALSE) {
	Text_Renderer = new TextRenderer();
	context_button = GL_FALSE;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = GL_FALSE;
}
Button::Button(const GLchar* text, const GLchar* shortcut) : Text(text), Shortcut(shortcut), Clicked(GL_FALSE), Visible(GL_FALSE) {
	Text_Renderer = new TextRenderer();
	context_button = GL_FALSE;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = GL_FALSE;
}
Button::Button(const GLchar* text) : Text(text), Shortcut("NULL"), Clicked(GL_FALSE), Visible(GL_FALSE) {
	Text_Renderer = new TextRenderer();
	context_button = GL_FALSE;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = GL_FALSE;
}
Button::~Button() {
	if (Text_Renderer)
		delete Text_Renderer;
}
void Button::render() {
	if (Visible == GL_TRUE) {
		if (InputManager::LeftClicked) {
			if (InputManager::MouseX > posx && InputManager::MouseX < posx + scalex && InputManager::MouseY > posy - scaley && InputManager::MouseY < posy) {
				Clicked = GL_TRUE;
			}
			else {
				Clicked = GL_FALSE;
			}
		}
		if (Clicked)
			printf("Clicked %s\n", Text.c_str());
		if (context_button == GL_TRUE) {
			scalex /= 5.5f;
			Text_Renderer->render(Text, posx + scalex / 4.5f, posy - 0.01f, scalex / 2.0f, scaley, textColor, 0.0f);
			if (Shortcut != "NULL") {
				Text_Renderer->render(Shortcut, posx + (scalex)*3.0f, posy - 0.01f, scalex / 2.0f, scaley, textColor, 0.0f);
			}
		}
		else {
			GLfloat text_scale_x = 4*scalex / (Text.length()+2);
			Text_Renderer->render(Text, posx + text_scale_x/4, posy - scaley/4, text_scale_x, scaley, textColor, 0.0f);
		}
	}
}