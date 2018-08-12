#include "InputManager.h"

static std::vector<GLint> KeyList;
double InputManager::MouseX = 0.0;
double InputManager::MouseY = 0.0;
bool InputManager::LeftClicked = false;
bool InputManager::RightClicked = false;
bool InputManager::Menu_Open = false;
GameState InputManager::State = MENU;

void InputManager::addKey(GLint key) {
	GLboolean key_exists = false;
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key)
			key_exists = true;
	}
	if (!key_exists)
		KeyList.push_back(key);
}
void InputManager::removeKey(GLint key) {
	GLboolean key_exists = false;
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key) {
			key_exists = true;
			KeyList.erase(KeyList.begin() + i);
			break;
		}
	}
}
bool InputManager::listContains(GLint key) {
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key)
			return true;	//List contains 'key'
	}
	return false;		//List does not contain 'key'
}
std::vector<GLint> InputManager::getKeyList() {
	return KeyList;
}