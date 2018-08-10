#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity {
public:
	Player(const char* img);
	~Player();
	void render();
private:
	
};
#endif
