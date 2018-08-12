#ifndef EYE_H
#define EYE_H
#include "Entity.h"
class Eye : public Entity {
public:
	Eye(const char* img_path);
	~Eye();
	void updateEye(float delta);
	void render();
private:
};
#endif;