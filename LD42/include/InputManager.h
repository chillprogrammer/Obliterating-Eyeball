#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <glad/glad.h>
#include <vector>
enum GameState { MENU, PLAYING, PAUSED };
struct InputManager {
	static double MouseX, MouseY;
	static bool LeftClicked, RightClicked, Menu_Open;
	static std::vector<GLint> getKeyList();
	static void addKey(GLint key);
	static void removeKey(GLint key);
	static bool listContains(GLint key);
	static GameState State;
};
#endif