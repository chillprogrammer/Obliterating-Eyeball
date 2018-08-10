#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_Hs
#include <glad/glad.h>
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <fstream>
struct ResourceManager {
	static void loadTexture(const GLchar* path, const GLchar* caller);
	static void bindTexture(const GLchar* caller);
	static Shader loadShader(const GLchar* vert_path, const GLchar* frag_path, const GLchar* caller);
	static void bindShader(const GLchar* caller);
	static void Revert();	//Clears all allocated memory (Essentially resetting the ResourceManager);
	//Pass uniforms to shader
	static void setUniformMat4(const char* caller, const glm::mat4 matrix, const char* shader_var);
	static void setUniformVec2(const char* caller, const glm::vec2 vec2, const char* shader_var);
	static void setUniformVec3(const char* caller, const glm::vec3 vec3, const char* shader_var);
	static void setUniform1f(const char* caller, const GLfloat f, const char* shader_var);
	static GLuint getShaderID(const GLchar* caller);	//Returns 0 if shader doesn't exist
	static GLuint getTextureID(const GLchar* caller);	//Returns 0 if texture doesn't exist
};
#endif