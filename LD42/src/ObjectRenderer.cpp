#include "ObjectRenderer.h"
#include "ResourceManager.h"

ObjectRenderer::ObjectRenderer() {
	if (ResourceManager::getShaderID("Rectangle") == 0)
		ResourceManager::loadShader("shaders/Rect_Shader.vs", "shaders/Rect_Shader.fs", "Rectangle");
	if (ResourceManager::getShaderID("Sprite") == 0)
		ResourceManager::loadShader("shaders/Sprite_Shader.vs", "shaders/Sprite_Shader.fs", "Sprite");
	if (ResourceManager::getShaderID("Image") == 0)
		ResourceManager::loadShader("shaders/Image_Shader.vs", "shaders/Image_Shader.fs", "Image");

	model = glm::mat4(1);
	float vertices[] = {
		// positions
		1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}
ObjectRenderer::~ObjectRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void ObjectRenderer::render(Button* but) {
	if (but->Visible) {
		this->model = glm::translate(glm::mat4(1), glm::vec3(but->posx, but->posy, 0.0f));
		ResourceManager::bindShader("Rectangle");
		glBindVertexArray(VAO);
		ResourceManager::setUniformMat4("Rectangle", this->model, "model");
		if (but->Hovered == true) {
			ResourceManager::setUniformVec3("Rectangle", but->hoverColor, "backColor");
		}
		else
			ResourceManager::setUniformVec3("Rectangle", but->backColor, "backColor");
		ResourceManager::setUniformVec3("Rectangle", but->borderColor, "borderColor");
		ResourceManager::setUniform1f("Rectangle", but->scalex, "scalex");
		ResourceManager::setUniform1f("Rectangle", but->scaley, "scaley");
		ResourceManager::setUniform1f("Rectangle", but->border_x, "border_x");
		ResourceManager::setUniform1f("Rectangle", but->border_y, "border_y");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		but->render();
	}
}
void ObjectRenderer::render(TextBox* tex) {
	if (tex->Visible) {
		this->model = glm::translate(glm::mat4(1), glm::vec3(tex->posx, tex->posy, 0.0f));
		ResourceManager::bindShader("Rectangle");
		glBindVertexArray(VAO);
		ResourceManager::setUniformMat4("Rectangle", this->model, "model");
		ResourceManager::setUniformVec3("Rectangle", tex->backColor, "backColor");
		ResourceManager::setUniform1f("Rectangle", tex->boxscalex, "scalex");
		ResourceManager::setUniform1f("Rectangle", tex->boxscaley, "scaley");
		ResourceManager::setUniform1f("Rectangle", tex->border_x, "border_x");
		ResourceManager::setUniform1f("Rectangle", tex->border_y, "border_y");
		if (tex->Clicked) {
			static double time = 0.0;
			static GLboolean toggle;
			if (glfwGetTime() - time > 0.2) {
				time = glfwGetTime();
				toggle = !toggle;
			}
			if (toggle)
				ResourceManager::setUniformVec3("Rectangle", tex->borderColor, "borderColor");
			else
				ResourceManager::setUniformVec3("Rectangle", tex->backColor, "borderColor");
		}
		else
			ResourceManager::setUniformVec3("Rectangle", tex->borderColor, "borderColor");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//Render Text ontop of textbox
		tex->render();
	}
}
void ObjectRenderer::render(Entity* ent) {
	if (ent->visible) {
		this->model = glm::translate(glm::mat4(1), glm::vec3(ent->getPos().x, ent->getPos().y, 0.0f));
		this->model = glm::rotate(model, glm::radians(ent->getAng()), glm::vec3(0.0f, 0.0f, 1.0f));
		ResourceManager::bindShader("Image");
		glBindVertexArray(VAO);
		ResourceManager::setUniformMat4("Image", Camera::Projection, "projection");
		ResourceManager::setUniformMat4("Image", this->model, "model");
		ResourceManager::setUniformVec3("Image", ent->color, "inColor");
		ResourceManager::setUniform1f("Image", ent->alpha, "alpha");
		ResourceManager::setUniform1f("Image", ent->getScale().x, "scalex");
		ResourceManager::setUniform1f("Image", ent->getScale().y, "scaley");
		ResourceManager::bindTexture(ent->getImage());
		ent->update(Camera::Delta);
		ent->render();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
void ObjectRenderer::render(Image* img) {
	if (img->visible) {
		this->model = glm::translate(glm::mat4(1), glm::vec3(img->pos.x, img->pos.y, 0.0f));
		GLchar* shader = img->shader;
		ResourceManager::bindShader(shader);
		glBindVertexArray(VAO);
		if(img->fixed)
			ResourceManager::setUniformMat4(shader, glm::mat4(1), "projection");
		else
			ResourceManager::setUniformMat4(shader, Camera::Projection, "projection");
		ResourceManager::setUniformMat4(shader, this->model, "model");
		ResourceManager::setUniformVec3(shader, img->color, "inColor");
		ResourceManager::setUniform1f(shader, img->alpha, "alpha");
		ResourceManager::setUniform1f(shader, img->scale.x, "scalex");
		ResourceManager::setUniform1f(shader, img->scale.y, "scaley");
		ResourceManager::bindTexture(img->path);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
void ObjectRenderer::render(GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, GLfloat border_x, GLfloat border_y, glm::vec3 backColor, glm::vec3 borderColor) {
	this->model = glm::translate(glm::mat4(1), glm::vec3(posx, posy, 0.0f));
	ResourceManager::bindShader("Rectangle");
	glBindVertexArray(VAO);
	ResourceManager::setUniformMat4("Rectangle", this->model, "model");
	ResourceManager::setUniformVec3("Rectangle", backColor, "backColor");
	ResourceManager::setUniformVec3("Rectangle", borderColor, "borderColor");
	ResourceManager::setUniform1f("Rectangle", scalex, "scalex");
	ResourceManager::setUniform1f("Rectangle", scaley, "scaley");
	ResourceManager::setUniform1f("Rectangle", border_x, "border_x");
	ResourceManager::setUniform1f("Rectangle", border_y, "border_y");
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}