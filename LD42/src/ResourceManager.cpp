#include "ResourceManager.h"
#include "stb_image.h"

static std::vector<Texture2D*> TextureList;
static std::vector<Shader*> ShaderList;

void ResourceManager::loadTexture(const GLchar* path, const GLchar* caller) {
	//Check if file exists
	bool exists = false;
	if (std::ifstream(path))
		exists = true;

	//If exists then load it up, if not then print error.
	if (exists) {
		int width, height, bpp;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* rgb = stbi_load(path, &width, &height, &bpp, 0);
		TextureList.push_back(new Texture2D());
		TextureList.back()->Generate(width, height, rgb);
		TextureList.back()->Caller = caller;
		stbi_image_free(rgb);
	}
	else {
		printf("ERROR: Attempted to load a nonexistant texture ( texture:%s )\n", caller);
	}
}
void ResourceManager::bindTexture(const GLchar* caller) {
	if (caller) {
		bool exists = false;
		for (unsigned int i = 0; i < TextureList.size(); i++) {
			if (TextureList[i]->Caller == caller) {
				TextureList[i]->Bind();
				exists = true;
			}
		}
		if (!exists) {
			printf("ERROR: Attempted to bind an unloaded texture ( texture:%s )\n", caller);
		}
	}
	else
		glBindTexture(GL_TEXTURE_2D, 0);
}
Shader ResourceManager::loadShader(const GLchar* vert_path, const GLchar* frag_path, const GLchar* caller) {
	//Check if file exists
	bool exists = false;
	if (std::ifstream(vert_path) && std::ifstream(frag_path))
		exists = true;

	if (exists) {
		Shader* shader = new Shader();
		shader->Compile(vert_path, frag_path, nullptr);
		shader->Caller = caller;
		ShaderList.push_back(shader);
		return *shader;
	}
	else {
		printf("ERROR: Attempted to load a nonexistant shader ( texture:%s )\n", caller);
		printf("ERROR: Undefined behavior expected ( texture:%s )\n", caller);
	}
	return *ShaderList[0];
}
void ResourceManager::bindShader(const GLchar* caller) {
	bool exists = false;
	for (unsigned int i = 0; i < ShaderList.size(); i++) {
		if (ShaderList[i]->Caller == caller) {
			ShaderList[i]->Use();
			exists = true;
		}
	}
	if (!exists) {
		printf("ERROR: Attempted to use an nongenerated shader ( shader:%s )\n", caller);
	}
}
void ResourceManager::Revert() {
	for (unsigned int i = 0; i < TextureList.size(); i++) {
		delete TextureList[i];
	}
	for (unsigned int i = 0; i < ShaderList.size(); i++) {
		delete ShaderList[i];
	}
}
void ResourceManager::setUniformMat4(const char* caller, const glm::mat4 matrix, const char* shader_var) {

	GLint loc = glGetUniformLocation(getShaderID(caller), shader_var);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		printf("ERROR: Attempted pass an invalid uniform mat4 (%s) to ( shader:%s )\n", shader_var, caller);
	}
}
void ResourceManager::setUniformVec2(const char* caller, const glm::vec2 vector2, const char* shader_var) {

	GLint loc = glGetUniformLocation(getShaderID(caller), shader_var);
	if (loc != -1)
	{
		glUniform2fv(loc, 1, glm::value_ptr(vector2));
	}
	else {
		printf("ERROR: Attempted pass an invalid uniform vec2 (%s) to ( shader:%s )\n", shader_var, caller);
	}
}
void ResourceManager::setUniformVec3(const char* caller, const glm::vec3 vector3, const char* shader_var) {

	GLint loc = glGetUniformLocation(getShaderID(caller), shader_var);
	if (loc != -1)
	{
		glUniform3fv(loc, 1, glm::value_ptr(vector3));
	}
	else {
		printf("ERROR: Attempted pass an invalid uniform vec3 (%s) to ( shader:%s )\n", shader_var, caller);
	}
}
void ResourceManager::setUniform1f(const char* caller, const GLfloat f, const char* shader_var) {

	GLint loc = glGetUniformLocation(getShaderID(caller), shader_var);
	if (loc != -1)
	{
		glUniform1f(loc, f);
	}
	else {
		printf("ERROR: Attempted pass an invalid uniform float (%s) to ( shader:%s )\n", shader_var, caller);
	}
}
GLuint ResourceManager::getShaderID(const GLchar* caller) {
	for (unsigned int i = 0; i < ShaderList.size(); i++) {
		if (ShaderList[i]->Caller == std::string(caller)) {
			return ShaderList[i]->ID;
		}
	}
	//Only get here if Shader is not loaded
	return 0;
}
GLuint ResourceManager::getTextureID(const GLchar* caller) {
	for (unsigned int i = 0; i < TextureList.size(); i++) {
		if (TextureList[i]->Caller == std::string(caller)) {
			return TextureList[i]->ID;
		}
	}
	//Only get here if Texture is not loaded
	return 0;
}