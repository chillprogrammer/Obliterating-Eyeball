#include "Eye.h"

Eye::Eye(const char* img_path) : Entity(img_path) {
	health = 100.0f;
	pos.x = 1.5f;
	pos.y = 2.0f;
	scale.x = 0.2f;
	scale.y = 0.2f;
}
Eye::~Eye() {

}