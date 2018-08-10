#include "TextBox.h"

TextBox::TextBox() 	: Text(""), Clicked(GL_FALSE), Visible(GL_FALSE), backColor(glm::vec3(1.0f, 1.0f, 1.0f)), borderColor(glm::vec3(0.0f, 0.0f, 0.0f)),
	textColor(glm::vec3(0.5f, 0.5f, 0.5f)), border_x(0.0f), border_y(0.0f) {
	Text_Renderer = new TextRenderer();
}
TextBox::TextBox(const GLchar* text) : Text(text), Clicked(GL_FALSE), Visible(GL_FALSE), backColor(glm::vec3(1.0f, 1.0f, 1.0f)),
borderColor(glm::vec3(0.0f, 0.0f, 0.0f)), textColor(glm::vec3(0.5f, 0.5f, 0.5f)), border_x(0.0f), border_y(0.0f) {
	Text_Renderer = new TextRenderer();
}
TextBox::~TextBox() {
	if (Text_Renderer)
		delete Text_Renderer;
}
void TextBox::keyPress(GLint key) {
	if (Clicked) {
		if (key == 259)
			Text = Text.substr(0, Text.length() - 1);
		else {
			GLchar ascii = (char)key;
			if (isdigit(ascii)) {
				Text += ascii;
			}
		}
		
	}
}
void TextBox::render() {
	if (Visible) {
		if (InputManager::LeftClicked) {
			if (InputManager::MouseX > posx && InputManager::MouseX < posx + boxscalex && InputManager::MouseY > posy - boxscaley && InputManager::MouseY < posy) {
				Clicked = GL_TRUE;
			}
			else {
				Clicked = GL_FALSE;
			}
		}
		if (Clicked && Text == default_text) {
			Text.clear();
		}
		if (!Clicked && Text.length() < 1) {
			Text = default_text;
		}
		if (Text_Renderer) {
			GLfloat text_scale_x = 4 * boxscalex / (Text.length() + 2);
			if(Text == default_text)
				Text_Renderer->render(Text, posx + text_scale_x / 4.0f, posy - textscaley / 4.0f, text_scale_x, textscaley, textColor, 0.0f);
			else
				Text_Renderer->render(Text, posx + textscalex / 4.0f, posy - textscaley / 4.0f, textscalex, textscaley, textColor, 0.0f);
		}
	}
}
