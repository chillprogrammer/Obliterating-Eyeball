#include "Image.h"
#include "ResourceManager.h"

Image::Image(const GLchar* file, const GLchar* shader_caller) {
	pos = glm::vec2(0.0f, 0.0f);
	scale = glm::vec2(0.0f, 0.0f);
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	alpha = 1.0f;
	if (!shader_caller)
		shader = _strdup("Image");
	else
		shader = _strdup(shader_caller);
	if (!file)
		path = nullptr;
	else {
		path = _strdup(file);
		if (ResourceManager::getTextureID(path) == 0)
			ResourceManager::loadTexture(path, path);
	}
	visible = true;
	fixed = false;
}
Image::~Image() {
	if(path)
		free(path);
	free(shader);
}