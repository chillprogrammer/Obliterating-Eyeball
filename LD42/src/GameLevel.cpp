#include "GameLevel.h"
#include "ResourceManager.h"

GameLevel::GameLevel(unsigned int level_id) {
	Width = 2;
	Height = 2;

	/*//Initialize the 2D array (Grid for the tile-based map)
	for (unsigned int x = 0; x < Width; x++) {
		std::vector<unsigned int> temp;
		for (unsigned int y = 0; y < Height; y++) {
			temp.push_back(0);
		}
		Grid.push_back(temp);
	}*/
	if (level_id == 0) {
		Width = 35;
		Height = 35;
		for (unsigned int x = 0; x < Width; x++) {
			std::vector<unsigned int> temp;
			for (unsigned int y = 0; y < Height; y++) {
				if (y < 5) {
					temp.push_back(2);
				}
				else if (y == 5) {
					temp.push_back(1);
				}
				else {
					temp.push_back(5);
				}
			}
			Grid.push_back(temp);
		}
	}
	/*//Create Level 0
	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			if (y < 5) {
				Grid[x][y] = 2;
			}
			else if (y == 5) {
				Grid[x][y] = 1;
			}
			else {
				Grid[x][y] = 5;
			}
		}
	}*/

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
			Sprite->render("content/overworld.png", Grid[x][y], x*tile_scale, y*tile_scale, 0.1f, 0.1f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, true);
		}
	}
}