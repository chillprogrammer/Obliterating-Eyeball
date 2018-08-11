#include "Button.h"

Button::Button() : Text("NULL"), Shortcut("NULL"), Pressed(false), Visible(true) {
	Text_Renderer = new TextRenderer();
	context_button = false;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = false;
	Hovered = false;
}
Button::Button(const GLchar* text, const GLchar* shortcut) : Text(text), Shortcut(shortcut), Pressed(false), Visible(false) {
	Text_Renderer = new TextRenderer();
	context_button = false;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = false;
	Hovered = false;
}
Button::Button(const GLchar* text) : Text(text), Shortcut("NULL"), Pressed(false), Visible(true) {
	Text_Renderer = new TextRenderer();
	context_button = false;
	hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	is_active = false;
	Hovered = false;
}
Button::~Button() {
	delete Text_Renderer;
}
void Button::render() {
	if (Visible == true) {
		if (InputManager::MouseX > posx - scalex && InputManager::MouseX < posx + scalex && InputManager::MouseY > posy - scaley && InputManager::MouseY < posy +scaley) {
			Hovered = true;
		}
		else {
			Hovered = false;
		}
		if (InputManager::LeftClicked) {
			if (Hovered == true) {
				Pressed = true;
			}
			else {
				Pressed = false;
			}
		}
		else {
			Pressed = false;
		}
		if (context_button == true) {
			scalex /= 5.5f;
			Text_Renderer->render(Text, posx + scalex / 4.5f, posy - 0.01f, scalex / 2.0f, scaley, textColor, 0.0f);
			if (Shortcut != "NULL") {
				Text_Renderer->render(Shortcut, posx + (scalex)*3.0f, posy - 0.01f, scalex / 2.0f, scaley, textColor, 0.0f);
			}
		}
		else {
			//GLfloat text_scale_x = 4*scalex / (Text.length()+2);
			float text_scale_x = 8*scalex / (Text.length()+2);
			Text_Renderer->render(Text, posx - scalex + text_scale_x/4, posy + scaley/2, text_scale_x, scaley*2, textColor, 0.0f);
		}
	}
}