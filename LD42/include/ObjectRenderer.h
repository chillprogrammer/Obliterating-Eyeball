#ifndef OBJECTRENDERER_H
#define OBJECTRENDERER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Button.h"
#include "TextBox.h"
#include "Entity.h"
#include "Camera.h"
#include "Image.h"

class ObjectRenderer {
public:
	ObjectRenderer();
	~ObjectRenderer();
	//Render Objects
	void render(Button*);
	void render(TextBox*);
	void render(Entity*);
	void render(Image*);
	//Render solid rectangle
	void render(GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, GLfloat border_x, GLfloat border_y, glm::vec3 backColor, glm::vec3 borderColor);
private:
	unsigned int VBO, VAO, EBO;
	glm::mat4 model;
};
#endif;