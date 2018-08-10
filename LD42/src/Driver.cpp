#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include <limits.h>
#include "al.h" 
#include "alc.h" 
#include <time.h>

Game* game;
int Width, Height;

void init_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
}

static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	game->key_callback(key, scancode, action, mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Width = width;
	Height = (int)(width/1.777f);
	game->resize(width, Height);
	glViewport(0, 0, width, width);
	glfwSetWindowSize(window, Width, Height);
}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	game->mouseMoved(2.0f*(GLfloat)xpos / Width - 1.0f, -2.0f*(GLfloat)ypos / Height + 1.0f);
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	game->mouse_button_callback(window, button, action, mods);
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	game->scroll_callback(window, xoffset, yoffset);
}
static void character_callback(GLFWwindow* window, unsigned int codepoint) {
	game->character_callback(window, codepoint);
	//printf("Keypressed=%c\n", (char)codepoint);
}
int main(void) {
	srand(time(NULL));
	//Core Variables before OpenGL context created
	short VERTICAL_SYNC = 0;
	//unsigned short FRAME_LIMITER = USHRT_MAX;
	unsigned short FRAME_LIMITER = 120;
	/////////////////////////////////////////////
	init_glfw();
	if (!glfwInit())
		exit(EXIT_FAILURE);
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	//Width = mode->width;
	//Height = mode->height;
	Width = mode->width/1.2;
	Height = mode->height/1.2;
	//window = glfwCreateWindow(Width, Height, "Untitled Space Game", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(Width, Height, "Joel's Platformer", NULL, NULL);
	//Set window callback events
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetKeyCallback(window, key_callback);
	////////////////////////////
	if (!window) {
		printf("Window not initialized\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Glad not initialized\n");
		exit(EXIT_FAILURE);
	}
	//Core Variable after OpenGL context created.
	game = new Game(window, Width, Height);
	glfwSwapInterval(VERTICAL_SYNC);
	/////////////////////////////////////////////
	// Enable OpenGL Tansparancy Capabilities.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, Width, Width);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//Wireframe Mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Texture Mode
	//////////////////////////////////////////
	float current_frame, last_frame, delta, startFPS;
	last_frame = (float)glfwGetTime();
	startFPS = (float)glfwGetTime();
	unsigned int frames = 0;

	while (!glfwWindowShouldClose(window)) {
		current_frame = (float)glfwGetTime();
		if (glfwGetTime() - startFPS >= 1.0) {
			startFPS = (float)glfwGetTime();
			game->FPS = frames;
			frames = 0;
		}
		if (current_frame - last_frame >= 1.0 / FRAME_LIMITER) {
			glfwSwapBuffers(window);
			frames++;
			glfwPollEvents();
			delta = current_frame - last_frame;
			game->update(delta);
			glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			last_frame = current_frame;
			game->render();
		}
	}
	if (game)
		delete game;
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

