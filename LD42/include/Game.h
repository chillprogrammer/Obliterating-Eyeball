#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "ResourceManager.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "ObjectRenderer.h"
#include "InputManager.h"
#include "Player.h"
#include <stdio.h>
#include "SoundEngine.h"
#include "GameLevel.h"
#include "MainMenu.h"
#include "Eye.h"

class Game
{
public:
	Game(GLFWwindow* window, const int W, const int H);
	~Game();
	void render();
	void update(float);
	void key_callback(int key, int scancode, int action, int mods);
	void resize(int, int);
	void mouseMoved(float xpos, float ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void character_callback(GLFWwindow* window, unsigned int codepoint);

	unsigned int FPS;
	float MouseX, MouseY;
private:
	int Width, Height;
	unsigned int Area;
	MainMenu* Menu;
	std::vector<GameLevel*> Levels;
	unsigned int Level;
	TextRenderer* Text;
	ObjectRenderer* Object;
	GLFWwindow* driver;

	//Entities
	Entity* Eyeball;
};
#endif