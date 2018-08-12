#include "GameLevel.h"
#include "ResourceManager.h"

GameLevel::GameLevel(unsigned int level_id) {
	switch (level_id) {
	case 0:
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
				if (y*tile_scale*1.777f < Camera::camera_pos.y + 1.2f && y*tile_scale*1.777f >Camera::camera_pos.y - 1.2f) {
					glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
					if (Grid[x][y] == 20)
						color = glm::vec3(0.388f, 0.608f, 1.0f);
					if (Grid[x][y] == 21)
						color = glm::vec3(0.188f, 0.0, 1.0f);
					Sprite->render("content/overworld.png", Grid[x][y], x*tile_scale, y*tile_scale*1.7777f, 0.1f, 0.1f*1.7777f, color, 0.0f, true);
				}
			}
		}
	}
}