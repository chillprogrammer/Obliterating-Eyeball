#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Camera.h"

SpriteRenderer::SpriteRenderer(const char* texture_path) {
	TILEMAP_WIDTH = 16.0f;
	TILEMAP_HEIGHT = 16.0f;

	//If Texture/Shader doesn't already exist in memory, then load it up
	if (ResourceManager::getShaderID("Sprite") == 0)
		ResourceManager::loadShader("shaders/Sprite_Shader.vs", "shaders/Sprite_Shader.fs", "Sprite");
	if (ResourceManager::getTextureID(texture_path) == 0)
		ResourceManager::loadTexture(texture_path, texture_path);

	model = glm::mat4(1);
	tilePosition = glm::vec2(0.0f, 0.0f);
	float vertices[] = {
		// positions
		1.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
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
SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void SpriteRenderer::setAppropriateTile(const char* texture_caller, const GLuint id) {
	if (strcmp(texture_caller, "Overworld") == 0) {
		this->tileDimensions = glm::vec2(TILEMAP_WIDTH, TILEMAP_HEIGHT);
		size_t index = 1;
		for (size_t row = 0; row < tileDimensions.y; row++) {
			for (size_t col = 0; col < tileDimensions.x; col++) {
				if (index == id)
					tilePosition = glm::vec2((GLfloat)col, (GLfloat)(tileDimensions.y - row - 1));
				index++;
			}
		}
	}
}
void SpriteRenderer::render(const char* texture_caller, const GLuint object_id, GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, glm::vec3 color, GLfloat rotation, bool is_world) {
	this->model = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	this->model = glm::translate(model, glm::vec3(posx, posy, 0.0f));
	
	ResourceManager::bindTexture(texture_caller);
	ResourceManager::bindShader("Sprite");

	glBindVertexArray(VAO);
	setAppropriateTile(texture_caller, object_id);
	if (object_id != 0) {
		if (is_world) {
			ResourceManager::setUniformMat4("Sprite", Camera::Projection, "projection");
		}
		ResourceManager::setUniformMat4("Sprite", this->model, "model");
		ResourceManager::setUniformVec2("Sprite", this->tilePosition, "tilePosition");
		ResourceManager::setUniformVec2("Sprite", this->tileDimensions, "tileDimensions");
		ResourceManager::setUniformVec3("Sprite", color, "inColor");
		ResourceManager::setUniform1f("Sprite", scalex, "scalex");
		ResourceManager::setUniform1f("Sprite", scaley, "scaley");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}