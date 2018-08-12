#include "GameLevel.h"
#include "ResourceManager.h"

GameLevel::GameLevel(unsigned int level_id) {
	//Default Entity Uninitialized
	Eyeball = nullptr;
	Guy = nullptr;

	switch (level_id) {
	case 0:
		Eyeball = new Eye("content/eyeball.png");
		Guy = new Player("content/player.png");
		Width = 35;
		Height = 25;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				if (y < 2) {
					temp.push_back(4);
				}
				else if (y < 5 && y >= 2) {
					temp.push_back(21);
				}
				else if (y == 6) {
					temp.push_back(18);
				}
				else if (y == 7) {
					temp.push_back(23);
				}
				else {
					temp.push_back(20);
				}
			}
			Grid.push_back(temp);
		}
		for (unsigned int x = 0; x < Width; x++) {
			for (unsigned int y = 0; y < Height; y++) {
				Grid[0][y] = 4;
				Grid[1][y] = 4;
				Grid[2][y] = 4;
				Grid[3][y] = 4;
				Grid[4][y] = 4;
				Grid[34][y] = 4;
				Grid[33][y] = 4;
				Grid[32][y] = 4;
				Grid[31][y] = 4;
				Grid[30][y] = 4;

				//Testing Purposes only
				Grid[7][7] = 20;
				Grid[8][7] = 20;
				Grid[9][7] = 20;
			}
		}
		break;
	default:
		Width = 2;
		Height = 2;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				temp.push_back(0);
			}
			Grid.push_back(temp);
		}
	}

	//Initialize Rendering Objects
	Sprite = new SpriteRenderer("content/overworld.png");
	Object = new ObjectRenderer();
}
GameLevel::~GameLevel() {
	delete Sprite;
	delete Object;
	if (Eyeball)
		delete Eyeball;
	if (Guy)
		delete Guy;
}
void GameLevel::update(float delta) {
	//Update Entities
	if (Eyeball) {
		Eyeball->update(delta);
		Eyeball->updateEye(delta);
	}
	if (Guy) {
		Guy->update(delta);
		Guy->updatePlayer(delta);
	}
}
void GameLevel::render() {
	static bool jumping = true;
	GLfloat tile_scale = 0.1f;
	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			GLfloat xpos = x * tile_scale;
			GLfloat ypos = y * tile_scale*1.7777f;
			GLfloat scalex = 0.1f;
			GLfloat scaley = 0.1f*1.7777f;
			if (xpos < Camera::camera_pos.x + 1.2f && xpos > Camera::camera_pos.x - 1.2f) {
				if (ypos < Camera::camera_pos.y + 1.2f && ypos >Camera::camera_pos.y - 1.2f) {
					glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
					if (Grid[x][y] == 20)
						color = glm::vec3(0.388f, 0.608f, 1.0f);
					if (Grid[x][y] == 21)
						color = glm::vec3(0.188f, 0.0, 1.0f);
					Sprite->render("content/overworld.png", Grid[x][y], xpos, ypos, scalex, scaley, color, 0.0f, true);
					
					//If game is not paused
					if (InputManager::State != PAUSED) {
						if ((InputManager::listContains(87) || InputManager::listContains(32)) && jumping == false) {	//W
							Guy->setVelocity(Guy->getVelocity().x, 0.2f);
							jumping = true;
						}
						if (InputManager::listContains(65)) { //A
							Guy->setVelocity(-Camera::Speed, Guy->getVelocity().y);
						}
						else if (InputManager::listContains(68)) { //D
							Guy->setVelocity(Camera::Speed, Guy->getVelocity().y);
						}
						else {
							Guy->setVelocity(0, Guy->getVelocity().y);
						}
					}
					else {
						Guy->setVelocity(0.0f, 0.0f);
					}
					//Check Collision
					if (Eyeball) {

					}
					if (Guy) {
						glm::vec2 player_pos = glm::vec2(Guy->getPos().x, Guy->getPos().y);
						if (Grid[x][y] == 18 || Grid[x][y] == 23) {
							if (player_pos.y < ypos + scaley && (player_pos.x < xpos + scalex && player_pos.x > xpos)) {
								Guy->setPosition(player_pos.x, ypos + scaley);
								jumping = false;
							}
							if (player_pos.x + Guy->getScale().x < 5 * scalex)
								Guy->setPosition(5 * scalex - Guy->getScale().x, player_pos.y);
							if (player_pos.x + Guy->getScale().x > 30 * scalex)
								Guy->setPosition(30 * scalex - Guy->getScale().x, player_pos.y);
						}
					}
				}
			}
		}
	}
	//Check if Camera should follow player
	if (Guy) {
		glm::vec2 player_pos = glm::vec2(Guy->getPos().x, Guy->getPos().y);
		if (InputManager::State == PLAYING) {
			if(jumping == false)
				Camera::setPosition(glm::vec3(Camera::camera_pos.x, player_pos.y, 0.0f));
			//else
				//Camera::setPosition(glm::vec3(Camera::camera_pos.x, player_pos.y, 0.0f));

			if (Camera::PLAYER_LOCK == true) {
				if (player_pos.x < 2.5f && player_pos.y > 1.0f && player_pos.y < 2.2f && player_pos.x > 1.0f) {
					Camera::setPosition(glm::vec3(player_pos.x, Camera::camera_pos.y, 0.0f));
				}
				//Stop Camera from leaving world boundaries during gameplay
				if (player_pos.x > 2.5f) {
					Camera::setPosition(glm::vec3(2.5f, Camera::camera_pos.y, 0.0f));
				}
				else if (player_pos.x < 1.0f) {
					Camera::setPosition(glm::vec3(1.0f, Camera::camera_pos.y, 0.0f));
				}
				if (player_pos.y > 2.2f) {
					Camera::setPosition(glm::vec3(Camera::camera_pos.x, 2.2f, 0.0f));
				}
				else if (player_pos.y < 1.0f) {
					Camera::setPosition(glm::vec3(Camera::camera_pos.x, 1.0f, 0.0f));
				}
			}
		}
	}
	//Render Entities
	if (Eyeball)
		Object->render(Eyeball);
	if (Guy)
		Object->render(Guy);
}