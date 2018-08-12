#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include "SpriteRenderer.h"
#include "Camera.h"

class GameLevel {
public:
	GameLevel(unsigned int id);
	~GameLevel();
	
	//Functions
	void update(float delta);
	void render();
private:
	unsigned int Width, Height;
	std::vector<std::vector<unsigned int>> Grid;
	SpriteRenderer* Sprite;
};
#endif