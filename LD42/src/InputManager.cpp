#include "InputManager.h"

static std::vector<GLint> KeyList;
GLdouble InputManager::MouseX = 0.0;
GLdouble InputManager::MouseY = 0.0;
GLboolean InputManager::LeftClicked = GL_FALSE;
GLboolean InputManager::RightClicked = GL_FALSE;
GLboolean InputManager::Menu_Open = GL_FALSE;
void InputManager::addKey(GLint key) {
	GLboolean key_exists = GL_FALSE;
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key)
			key_exists = GL_TRUE;
	}
	if (!key_exists)
		KeyList.push_back(key);
}
void InputManager::removeKey(GLint key) {
	GLboolean key_exists = GL_FALSE;
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key) {
			key_exists = GL_TRUE;
			KeyList.erase(KeyList.begin() + i);
			break;
		}
	}
}
GLboolean InputManager::listContains(GLint key) {
	for (unsigned int i = 0; i < KeyList.size(); i++) {
		if (KeyList[i] == key)
			return GL_TRUE;	//List contains 'key'
	}
	return GL_FALSE;		//List does not contain 'key'
}
std::vector<GLint> InputManager::getKeyList() {
	return KeyList;
}