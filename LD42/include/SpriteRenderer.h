#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class SpriteRenderer {
public:
	SpriteRenderer(const char* texture_caller);
	~SpriteRenderer();
	void setAppropriateTile(const char* texture_caller, const GLuint id);
	void render(const char* texture_caller, const GLuint object_id, GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, glm::vec3 color, GLfloat rotation, bool is_world);
private:
	unsigned int VBO, VAO, EBO;
	glm::vec2 tilePosition, tileDimensions;
	glm::mat4 model;
	GLfloat TILEMAP_WIDTH, TILEMAP_HEIGHT;
};
#endif
