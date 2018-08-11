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
	ObjectRenderer* Object;
	SpriteRenderer* Sprite;
	std::vector<Button*> Buttons;
	GLFWwindow* window;
};
#endif