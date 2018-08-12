#include "GameLevel.h"
#include "ResourceManager.h"
//Note: the bridge spans left-to-right on y = 6 and y = 7.

GameLevel::GameLevel(unsigned int level_id) {
	//Default Entity Uninitialized
	Eyeball = nullptr;
	Guy = nullptr;
	Projectile = nullptr;

	switch (level_id) {
	case 0:
		Eyeball = new Eye("content/eyeball.png");
		Guy = new Player("content/player.png");
		Projectile = new Entity("content/projectile.png");
		Projectile->color = glm::vec3(0.0f, 0.0f, 1.0f);
		Projectile->visible = false;
		Width = 35;
		Height = 25;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				if (y < 2) {
					temp.push_back(4);
				}
				else if (y < 4 && y >= 2) {
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

				/*//Testing Purposes only
				Grid[7][7] = 10;
				Grid[8][7] = 10;
				Grid[9][7] = 10;
				Grid[7][6] = 10;
				Grid[8][6] = 10;
				Grid[9][6] = 10;
				*/
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
void GameLevel::Restart(unsigned int level_id) {
	Guy->setVelocity(0.0f, 0.0f);
	Guy->setPosition(1.51f, 1.5f);
	Grid.clear();
	switch (level_id) {
	case 0:
		Projectile->color = glm::vec3(0.0f, 0.0f, 1.0f);
		Projectile->visible = false;
		Width = 35;
		Height = 25;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				if (y < 2) {
					temp.push_back(4);
				}
				else if (y < 4 && y >= 2) {
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

				/*//Testing Purposes only
				Grid[7][7] = 10;
				Grid[8][7] = 10;
				Grid[9][7] = 10;
				Grid[7][6] = 10;
				Grid[8][6] = 10;
				Grid[9][6] = 10;
				*/
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
}
void GameLevel::update(float delta) {
	//Update Entities
	if (Projectile && Eyeball) {
		//Eyeball fires projectile
		static glm::vec2 projectile_velocity = glm::vec2(0.0f, 0.0f);
		if (!Eyeball->attacking) {
			Projectile->setPosition(Eyeball->getPos().x - 0.5 + Eyeball->pupil_pos.x, Eyeball->getPos().y - 0.5 + Eyeball->pupil_pos.y);
			projectile_velocity.x = Eyeball->pupil_pos.x - 0.5f;
			projectile_velocity.y = Eyeball->pupil_pos.y - 0.5f;
		}
		else {
			Projectile->visible = true;
			Projectile->setVelocity(projectile_velocity.x, projectile_velocity.y);
		}
		
		Projectile->update(delta);
	}
	if (Eyeball) {
		Eyeball->update(delta);
		Eyeball->updateEye(delta);

	}
	if (Guy) {
		Guy->update(delta);
		Guy->updatePlayer(delta);
	}
	if (Guy && Eyeball) {
		//Makes sure the Eyeball is staring at the Player at all times
		glm::vec2 distance;
		distance.x = Eyeball->getPos().x - Guy->getPos().x;
		distance.y = Eyeball->getPos().y - Guy->getPos().y;
		GLfloat magnitude = (GLfloat)sqrt(distance.x*distance.x + distance.y*distance.y);
		Eyeball->pupil_pos = glm::vec2(-distance.x/(magnitude*4) + 0.5f, -distance.y/ (magnitude*4) + 0.5f);
		//Makes sure the eyeball follows the player
		glm::vec2 player_pos = glm::vec2(Guy->getPos().x, Guy->getPos().y);
		glm::vec2 eyeball_pos = glm::vec2(Eyeball->getPos().x, Eyeball->getPos().y);
		if (InputManager::State != PAUSED) {
			if (player_pos.x > eyeball_pos.x) {
				Eyeball->setVelocity(Eyeball->getVelocity().x + 0.1f*delta, Eyeball->getVelocity().y);
			}
			else {
				Eyeball->setVelocity(Eyeball->getVelocity().x - 0.1f*delta, Eyeball->getVelocity().y);
			}
			if (Eyeball->getPos().y > 2.4f) {
				Eyeball->setPosition(Eyeball->getPos().x, 2.4f);
				Eyeball->setVelocity(Eyeball->getVelocity().x, -0.1f);
			}
			else if (Eyeball->getPos().y < 2.0f) {
				Eyeball->setPosition(Eyeball->getPos().x, 2.0f);
				Eyeball->setVelocity(Eyeball->getVelocity().x, 0.1f);
			}
		}
		else {
			Eyeball->setVelocity(0.0f, 0.0f);
		}
	}
}
void GameLevel::render() {
	static bool jumping = true;
	GLfloat tile_scale = 0.1f;
	//Player Fell Off
	if(InputManager::State == PLAYING) {
		if (Guy->getPos().y < 4 * tile_scale*1.7777f) {
			InputManager::State = DIED;
			Camera::PLAYER_LOCK = false;
			SoundEngine::stopSound("sounds/game-song.wav");
			SoundEngine::playSound("sounds/menu-theme.wav", glm::vec2(0.0f, 0.0f), true);
		}
	}
	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			GLfloat xpos = x * tile_scale;
			GLfloat ypos = y * tile_scale*1.7777f;
			GLfloat scalex = 0.1f;
			GLfloat scaley = 0.1f*1.7777f;
			//if (xpos < Camera::camera_pos.x + 1.2f && xpos > Camera::camera_pos.x - 1.2f) {
			//	if (ypos < Camera::camera_pos.y + 1.2f && ypos >Camera::camera_pos.y - 1.2f) {
					glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
					if (Grid[x][y] == 20 || Grid[x][y] == 10 || Grid[x][y] == 11)
						color = glm::vec3(0.388f, 0.608f, 1.0f);
					if (Grid[x][y] == 21)
						color = glm::vec3(0.96f, 0.447f, 0.035f);

					//Mouse Hovering over damaged bridge Events go here!
					if (InputManager::State == PLAYING) {
						if ((y == 6 || y == 7) && (Grid[x][y] != 18 && (Grid[x][y] != 23))) {
							if (InputManager::MouseX > xpos - Camera::camera_pos.x && InputManager::MouseX < xpos + scalex - Camera::camera_pos.x) {
								if (InputManager::MouseY > ypos - scaley - Camera::camera_pos.y && InputManager::MouseY < ypos - Camera::camera_pos.y) {
									if (abs(xpos - Guy->getPos().x) < scalex * 3) {
										color *= 0.5f;
										if (InputManager::LeftClicked) {
											if (y == 6)
												Grid[x][y] = 18;
											else if (y == 7)
												Grid[x][y] = 23;
										}
									}
								}
							}
						}
					}
					Sprite->render("content/overworld.png", Grid[x][y], xpos, ypos, scalex, scaley, color, 0.0f, true);

					//If game is not paused
					if (InputManager::State == PLAYING || InputManager::State == MENU) {
						if ((InputManager::listContains(87) || InputManager::listContains(32)) && jumping == false) {	//W
							Guy->setVelocity(Guy->getVelocity().x, 0.4f);
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
					if (Guy) {
						glm::vec2 player_pos = glm::vec2(Guy->getPos().x, Guy->getPos().y);
						if (Grid[x][y] == 18 || Grid[x][y] == 23) {
							if (player_pos.y < ypos + scaley && (player_pos.x < xpos + scalex * 1.25 && player_pos.x > xpos - scalex * .25)) {
								if (player_pos.y >= ypos) {
									Guy->setPosition(player_pos.x, ypos + scaley);
									jumping = false;
								}
							}
							if (player_pos.x + Guy->getScale().x < 5 * scalex)
								Guy->setPosition(5 * scalex - Guy->getScale().x, player_pos.y);
							if (player_pos.x + Guy->getScale().x > 30 * scalex)
								Guy->setPosition(30 * scalex - Guy->getScale().x, player_pos.y);
						}
					}
					if (Eyeball) {
						glm::vec2 eyeball_pos = glm::vec2(Eyeball->getPos().x, Eyeball->getPos().y);
						if (Grid[x][y] == 18 || Grid[x][y] == 23) {
							if (eyeball_pos.y < ypos + scaley && (eyeball_pos.x < xpos + scalex && eyeball_pos.x > xpos)) {
								Eyeball->setPosition(eyeball_pos.x, ypos + scaley);
							}
							if (eyeball_pos.x - Eyeball->getScale().x < 5 * scalex)
								Eyeball->setPosition(5 * scalex + Eyeball->getScale().x, eyeball_pos.y);
							if (eyeball_pos.x + Eyeball->getScale().x > 30 * scalex)
								Eyeball->setPosition(30 * scalex - Eyeball->getScale().x, eyeball_pos.y);
						}
					}
				//}
			//}
			if (Projectile) {
				glm::vec2 projectile_pos = glm::vec2(Projectile->getPos().x, Projectile->getPos().y);
				glm::vec2 projectile_scale = glm::vec2(Projectile->getScale().x, Projectile->getScale().y);
				if (Grid[x][y] == 18 || Grid[x][y] == 23) {
					if (projectile_pos.x + Projectile->getScale().x/2 > xpos && projectile_pos.x - Projectile->getScale().x/2 < xpos + scalex && projectile_pos.y + Projectile->getScale().y/2 > ypos && projectile_pos.y - Projectile->getScale().y/2 < ypos + scaley) {
						Grid[x][y] = 20;
						Grid[x + 1][y] = 20;
						Grid[x - 1][y] = 20;
						Grid[x][y - 1] = 20;
						//Eyeball->attacking = false;
						//Projectile->visible = false;
					}
				}
			}
		}
	}
	if (Projectile->getPos().y < 2 * tile_scale*1.777f) {
		Eyeball->attacking = false;
		Projectile->visible = false;
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
	if (Projectile)
		Object->render(Projectile);
	if (Guy)
		Object->render(Guy);
}