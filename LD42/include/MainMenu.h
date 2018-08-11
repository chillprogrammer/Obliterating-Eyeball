#ifndef MAINMENU_H
#define MAINMENU_H
#include "ObjectRenderer.h"
#include "SpriteRenderer.h"
#include <vector>

struct MainMenu {
	MainMenu();
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
};
#endif