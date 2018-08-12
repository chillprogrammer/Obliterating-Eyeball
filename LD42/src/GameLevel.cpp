#include "GameLevel.h"
#include "ResourceManager.h"

GameLevel::GameLevel(unsigned int level_id) {
	/*//Initialize the 2D array (Grid for the tile-based map)
	for (unsigned int x = 0; x < Width; x++) {
		std::vector<unsigned int> temp;
		for (unsigned int y = 0; y < Height; y++) {
			temp.push_back(0);
		}
		Grid.push_back(temp);
	}*/
	switch (level_id) {
	case 0:
		Width = 35;
		Height = 25;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				if (y < 8) {
					temp.push_back(4);
				}
				else if (y == 8) {
					temp.push_back(1);
				}
				else {
					temp.push_back(20);
				}
			}
			Grid.push_back(temp);
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

	Sprite = new SpriteRenderer("content/overworld.png");
}
GameLevel::~GameLevel() {
	delete Sprite;
}
void GameLevel::update(float delta) {

}
void GameLevel::render() {
	GLfloat tile_scale = 0.1f;
	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			if (x*tile_scale < Camera::camera_pos.x + 1.2f && x*tile_scale > Camera::camera_pos.x - 1.2f) {
				if(y*tile_scale*1.777f < Camera::camera_pos.y + 1.2f && y*tile_scale*1.777f >Camera::camera_pos.y - 1.2f)
					Sprite->render("content/overworld.png", Grid[x][y], x*tile_scale, y*tile_scale*1.7777f, 0.1f, 0.1f*1.7777f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, true);
			}
		}
	}
}