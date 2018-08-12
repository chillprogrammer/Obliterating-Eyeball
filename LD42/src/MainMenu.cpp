#include "MainMenu.h"
#include "SoundEngine.h"

MainMenu::MainMenu(GLFWwindow* driver) {
	window = driver;
	visible = true;
	//Initialize Pointers
	Text = new TextRenderer();
	Object = new ObjectRenderer();
	Made = new Made_Menu(Object, Text);

	for (unsigned int i = 0; i < 3; i++) {
		Buttons.push_back(new Button());
		switch (i) {
		case 0:
			Buttons[i]->Text = "Play";
			Buttons[i]->scalex = 0.15f;
			Buttons[i]->border_x = 0.025f;
			break;
		case 1:
			Buttons[i]->Text = "Credits";
			Buttons[i]->scalex = 0.2f;
			Buttons[i]->border_x = 0.01f;
			break;
		case 2:
			Buttons[i]->Text = "Exit";
			Buttons[i]->scalex = 0.12f;
			Buttons[i]->border_x = 0.025f;
			break;
		}
		Buttons[i]->backColor = glm::vec3(0.70588f, 0.99216f, 0.737255f);
		Buttons[i]->borderColor = glm::vec3(0.0f, 0.0f, 0.0f);
		Buttons[i]->hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
		Buttons[i]->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
		Buttons[i]->border_y = 0.1f;
		Buttons[i]->posx = 0.0f;
		Buttons[i]->posy = 0.1f - 0.25f*i;
		Buttons[i]->scaley = 0.05f;
	}
	//SoundEngine::playSound("sounds/menu-theme.wav", glm::vec2(0.0f, 0.0f), true);
}
MainMenu::~MainMenu() {
	delete Made;
	delete Object;
	delete Text;
	for (unsigned int i = 0; i < Buttons.size(); i++) {
		delete Buttons[i];
	}
}
void MainMenu::update(float delta) {

}
void MainMenu::render() {
	if (visible) {
		if (!Made->visible) {
			for (unsigned int i = 0; i < Buttons.size(); i++) {
				Buttons[i]->Visible = true;
			}
		}
		else {
			for (unsigned int i = 0; i < Buttons.size(); i++) {
				Buttons[i]->Visible = false;
			}
		}

		for (unsigned int i = 0; i < Buttons.size(); i++) {
			Object->render(Buttons[i]);
		}
		if (Buttons[0]->Pressed) {
			visible = false;
			//SoundEngine::stopSound("sounds/menu-theme.wav");
			//SoundEngine::playSound("sounds/game-song.wav", glm::vec2(0.0f, 0.0f), true);
		}
		else if (Buttons[1]->Pressed) {
			Made->visible = true;
		}
		else if (Buttons[2]->Pressed) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		//Render Made Menu
		if (Made->visible) {
			Made->render();
		}

		//Render Title
		static float rotation = 0.0f;
		static float rate = 0.15f;
		if (rotation > 15.0f)
			rate = -0.15;
		if (rotation < -15.0f)
			rate = 0.15;
		rotation += rate;
		Text->render("Game Title!", -0.25f, 0.8f, 0.2f, 0.2*1.777f, glm::vec3(0.72157f, 0.52549f, 0.04314f), rotation);
	}
	else {
		for (unsigned int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->Visible = false;
		}
	}
}
//The screen that pops up when you click the "How the Game Was Made" button.
MainMenu::Made_Menu::Made_Menu(ObjectRenderer* O, TextRenderer* T) {
	Object = O;
	Text = T;
	visible = false;
	Back = new Button("Back");
	Back->scalex = 0.15f;
	Back->border_x = 0.025f;
	Back->backColor = glm::vec3(0.70588f, 0.99216f, 0.737255f);
	Back->borderColor = glm::vec3(0.0f, 0.0f, 0.0f);
	Back->hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
	Back->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
	Back->border_y = 0.1f;
	Back->posx = 0.5f;
	Back->posy = -0.5f;
	Back->scaley = 0.05f;
}
MainMenu::Made_Menu::~Made_Menu() {
	delete Back;
}
void MainMenu::Made_Menu::render() {
	if (visible) {
		Object->render(Back);
		if (Back->Pressed) {
			visible = false;
		}
		float text_scale = 0.1f;
		Text->render("Programmer:", -0.3f, 0.0f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Artist:", -0.3f, -0.15f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Sound Guy:", -0.3f, -0.30f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Joel Schechter", 0.0f, 0.0f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		Text->render("Joel Schechter", 0.0f, -0.15f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		Text->render("Joel Schechter", 0.0f, -0.30f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	}
}