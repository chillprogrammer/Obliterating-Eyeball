#include <stdio.h>
#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

Game::Game(GLFWwindow* window, const int w, const int h) : driver(window), Width(w), Height(h), FPS(0) {
	//initalize Sound Engine
	SoundEngine::Initialize();

	//Center Camera with zoom (x1)
	Camera::zoom(1.0f);
	Camera::setPosition(glm::vec3(0.5f, 0.3f, 0.0f));

	//Initialize Objects
	Text = new TextRenderer();
	Object = new ObjectRenderer();
	Camera::PLAYER_LOCK = false;

	GameLevel* Lvl1 = new GameLevel(0);
	Levels.push_back(Lvl1);
	Level = 0;
}
Game::~Game() {
	//Clear Programs
	SoundEngine::Revert();
	ResourceManager::Revert();
	//Delete Objects
	delete Text;
	delete Object;
	for (unsigned int i = 0; i < Levels.size(); i++) {
		delete Levels[i];
	}
}
void Game::resize(int w, int h) {
	this->Width = w;
	this->Height = h;
}
void Game::character_callback(GLFWwindow* window, unsigned int codepoint) {
	
}
void Game::key_callback(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		InputManager::addKey(key);
		printf("%d\n", key);
	}
	if (action == GLFW_RELEASE) {
		InputManager::removeKey(key);
	}
}
void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}
void Game::render() {
	//Render the selected level
	Levels[Level]->render();

	//Show FPS
	Text->render("FPS: " + std::to_string(FPS), -0.95f, 0.1f, 0.1f, 0.1 / 1.777f, glm::vec3(0.8f, 0.8f, 0.8f), 0.0f);

	//Refresh the Sound Program - memory gets deallocated from buffers when it is not used anymore.
	SoundEngine::Refresh();
}
void Game::mouseMoved(float xpos, float ypos) {
	InputManager::MouseX = xpos;
	InputManager::MouseY = ypos;
}
void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		InputManager::LeftClicked = GL_TRUE;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		InputManager::LeftClicked = GL_FALSE;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		InputManager::RightClicked = GL_TRUE;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		InputManager::RightClicked = GL_FALSE;
	}
}
void Game::update(float delta) {
	//Update Static Delta Variable
	Camera::Delta = delta;

	//Retrieve KeyList from the InputManager
	std::vector<GLint> KeyList = InputManager::getKeyList();

	//Angle Player
	if (InputManager::listContains(263)) { //Left Arrow

	}
	if (InputManager::listContains(262)) { //Right Arrow

	}
	if (InputManager::listContains(340) || InputManager::listContains(344)) {	//Shift Keys
		Camera::Speed = Camera::DEFAULT_SPEED*2.0f;
	}
	else {
		Camera::Speed = Camera::DEFAULT_SPEED;
	}
	//Move Player
	if (InputManager::listContains(87)) {	//W
		Camera::translateMatrix(glm::vec3(0.0f, -Camera::Speed, 0.0f));
	}
	if (InputManager::listContains(83)) {	//S
		Camera::translateMatrix(glm::vec3(0.0f, Camera::Speed, 0.0f));
	}
	if (InputManager::listContains(65)) { //A
		Camera::translateMatrix(glm::vec3(Camera::Speed, 0.0f, 0.0f));
	}
	if (InputManager::listContains(68)) { //D
		Camera::translateMatrix(glm::vec3(-Camera::Speed, 0.0f, 0.0f));
	}
	//If the camera should lock onto the player
	if(Camera::PLAYER_LOCK == GL_TRUE) {
		//Camera::setPosition(glm::vec3(player->getPos().x, player->getPos().y, 0.0f));
	}

	Levels[Level]->update(delta);
}