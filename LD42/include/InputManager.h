#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <glad/glad.h>
#include <vector>
struct InputManager {
	static GLdouble MouseX, MouseY;
	static GLboolean LeftClicked, RightClicked, Menu_Open;
	static std::vector<GLint> getKeyList();
	static void addKey(GLint key);
	static void removeKey(GLint key);
	static GLboolean listContains(GLint key);
};
#endif