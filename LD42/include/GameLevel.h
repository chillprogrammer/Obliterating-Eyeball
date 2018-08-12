#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include "SpriteRenderer.h"
#include "Camera.h"
#include "ObjectRenderer.h"
#include "Eye.h"
#include "Player.h"
#include <cmath>

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
	ObjectRenderer* Object;
	//Entities
	Entity* Eyeball, *Guy, *Projectile;
};
#endif