#include "MainMenu.h"
#include "SoundEngine.h"

MainMenu::MainMenu() {
	visible = true;
	Object = new ObjectRenderer();
	Sprite = new SpriteRenderer("content/overworld.png");
	for (unsigned int i = 0; i < 3; i++) {
		Buttons.push_back(new Button());
		switch (i) {
		case 0:
			Buttons[i]->Text = "Play";
			Buttons[i]->scalex = 0.15f;
			Buttons[i]->border_x = 0.025f;
			break;
		case 1:
			Buttons[i]->Text = "How The Game Was Made";
			Buttons[i]->scalex = 0.3f;
			Buttons[i]->border_x = 0.01f;
			break;
		case 2:
			Buttons[i]->Text = "Exit";
			Buttons[i]->scalex = 0.12f;
			Buttons[i]->border_x = 0.025f;
			break;
		}
		Buttons[i]->backColor = glm::vec3(1.0f, 0.87f, 0.8f);
		Buttons[i]->borderColor = glm::vec3(0.3f, 0.3f, 0.3f);
		Buttons[i]->hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
		Buttons[i]->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
		Buttons[i]->border_y = 0.1f;
		Buttons[i]->posx = 0.0f;
		Buttons[i]->posy = 0.1f - 0.25f*i;
		Buttons[i]->scaley = 0.05f;
	}
	SoundEngine::playSound("sounds/menu-theme.wav", glm::vec2(0.0f, 0.0f), true);
}
MainMenu::~MainMenu() {
	delete Object;
	delete Sprite;
	for (unsigned int i = 0; i < Buttons.size(); i++) {
		delete Buttons[i];
	}
}
void MainMenu::update(float delta) {

}
void MainMenu::render() {
	if (visible) {
		for (unsigned int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->Visible = true;
			Object->render(Buttons[i]);
		}
		if (Buttons[0]->Pressed) {
			printf("CLICKED!!!!!\n");
			SoundEngine::stopSound("sounds/menu-theme.wav");
		}
	}
	else {
		for (unsigned int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->Visible = false;
		}
	}
}