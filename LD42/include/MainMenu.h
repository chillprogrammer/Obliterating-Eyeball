#ifndef MAINMENU_H
#define MAINMENU_H
#include "ObjectRenderer.h"
#include "SpriteRenderer.h"
#include <vector>
#include <GLFW/glfw3.h>

struct MainMenu {
	MainMenu(GLFWwindow*);
	~MainMenu();
	//Functions
	void update(float delta);
	void render();
	//Variables
	bool visible;
private:
	TextRenderer * Text;
	ObjectRenderer* Object;
	SpriteRenderer* Sprite;
	std::vector<Button*> Buttons;
	GLFWwindow* window;
	float eyeball_rotation;
	glm::vec2 oblit_pos;

	//The screen that pops up when you click the "How the Game Was Made" button.
	struct Made_Menu {
		void render();
		Made_Menu(ObjectRenderer*, TextRenderer*);
		~Made_Menu();
		Button* Back;
		bool visible;
		ObjectRenderer* Object;
		TextRenderer* Text;
	};
	Made_Menu * Made;
};
#endif