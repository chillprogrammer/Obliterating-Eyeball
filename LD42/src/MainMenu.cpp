#include "MainMenu.h"
#include "SoundEngine.h"

MainMenu::MainMenu(GLFWwindow* driver) {
	window = driver;
	visible = true;
	//Initialize Pointers
	Text = new TextRenderer();
	Object = new ObjectRenderer();
	Made = new Made_Menu(Object, Text);

	glm::vec2 oblit_pos = glm::vec2(-0.5f, 0.8f);

	for (unsigned int i = 0; i < 4; i++) {
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
			Buttons[i]->border_x = 0.015f;
			break;
		case 2:
			Buttons[i]->Text = "Exit";
			Buttons[i]->scalex = 0.12f;
			Buttons[i]->border_x = 0.025f;
			break;
		}
		Buttons[i]->backColor = glm::vec3(0.40588f, 0.69216f, 0.437255f);
		Buttons[i]->borderColor = glm::vec3(0.0f, 0.0f, 0.0f);
		Buttons[i]->hoverColor = glm::vec3(0.5f, 0.5f, 0.5f);
		Buttons[i]->textColor = glm::vec3(1.0f, 1.0f, 1.0f);
		Buttons[i]->border_y = 0.1f;
		Buttons[i]->posx = 0.0f;
		Buttons[i]->posy = 0.3f - 0.25f*i;
		Buttons[i]->scaley = 0.08f;
	}
	eyeball_rotation = 0.0f;
	SoundEngine::playSound("sounds/menu-theme.wav", glm::vec2(0.0f, 0.0f), true);
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
	//Update Title position and rotation
	static float rate = 15.0f;
	if (eyeball_rotation > 15.0f) {
		eyeball_rotation = 15.0f;
		rate *= -1;
	}
	if (eyeball_rotation < -15.0f) {
		eyeball_rotation = -15.0f;
		rate *= -1;
	}
	eyeball_rotation += rate*delta;
	static glm::vec2 oblit_vel = glm::vec2(0.3f, 0.15f);
	oblit_pos.x += oblit_vel.x*delta;
	oblit_pos.y += oblit_vel.y*delta;
	if (oblit_pos.x > -0.48f) {
		oblit_pos.x = -0.48f;
		oblit_vel.x *= -1;
	}
	else if (oblit_pos.x < -0.52f) {
		oblit_pos.x = -0.52f;
		oblit_vel.x *= -1;
	}
	if (oblit_pos.y > 0.82f) {
		oblit_pos.y = 0.82f;
		oblit_vel.y *= -1;
	}
	else if (oblit_pos.y < 0.78f) {
		oblit_pos.y = 0.78f;
		oblit_vel.y *= -1;
	}
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
			if (InputManager::State == MENU)
				Buttons[0]->Text = "Play";
			else if (InputManager::State == PAUSED)
				Buttons[0]->Text = "Resume";
			Object->render(Buttons[i]);
		}
		if (Buttons[0]->Pressed) {
			Camera::PLAYER_LOCK = true;
			InputManager::State = PLAYING;
			visible = false;
			SoundEngine::stopSound("sounds/menu-theme.wav");
			SoundEngine::playSound("sounds/game-song.wav", glm::vec2(0.0f, 0.0f), true);
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
	}
	else {
		for (unsigned int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->Visible = false;
		}
	}

	//Render Game Title (Obliterate vibrates, and Eyeball rotates)
	Text->render("Obliterating", oblit_pos.x, oblit_pos.y, 0.2f, 0.2*1.777f, glm::vec3(0.99f, 0.52549f, 0.04314f), 0.0f);
	Text->render("Eyeball!", 0.20f, 0.8f, 0.2f, 0.2*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), eyeball_rotation);

	//If at Pause Menu, then display PAUSE
	if (InputManager::State == PAUSED) {
		static float paused_blink = 0.0f;
		static bool color_toggle = true;
		paused_blink += 1.0f*Camera::Delta;
		static glm::vec3 pause_color = glm::vec3(1.0f, 0.9f, 0.9f);
		if (paused_blink > 1.0f) {
			if (color_toggle) {
				pause_color = glm::vec3(1.0f, 0.2f, 0.2f);
				color_toggle = false;
			}
			else {
				pause_color = glm::vec3(1.0f, 0.9f, 0.9f);
				color_toggle = true;
			}
			paused_blink = 0.0f;
		}
		Text->render("<Paused>", -0.20f, 0.65f, 0.2f, 0.2*1.777f, pause_color, 0.0f);
	}

	//Render Goal
	Text->render("Goal: Survive for as long as you can!", -0.90f, -0.4f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("The eyeball destroys the bridge.", -0.90f, -0.55f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("If you fall in the lava - you die.", -0.90f, -0.7f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("Eventually you might run out of space.", -0.90f, -0.85f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);

	//Render Controls
	Text->render("Controls:", 0.30f, 0.3f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("A = Move Left", 0.30f, 0.15f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("D = Move Right", 0.30f, 0.0f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("W or SPACE = Jump", 0.30f, -0.15f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("LEFT CLICK = Place Bridge Pieces", 0.18f, -0.30f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
	Text->render("ESCAPE = Pause Game", 0.30f, -0.45f, 0.1f, 0.1*1.777f, glm::vec3(0.5f, 0.8f, 0.5f), 0.0f);
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
	Back->scaley = 0.08f;
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
		Text->render("Programmer:", -0.6f, 0.15f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Artist:", -0.6f, 0.0f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Sound Guy:", -0.6f, -0.15f, text_scale, text_scale*1.777f, glm::vec3(0.92157f, 0.22549f, 0.04314f), 0.0f);
		Text->render("Joel Schechter", -0.3f, 0.15f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		Text->render("Joel Schechter", -0.3f, 0.0f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		Text->render("Joel Schechter", -0.3f, -0.15f, text_scale, text_scale*1.777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	}
}