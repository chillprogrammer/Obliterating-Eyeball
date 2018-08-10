#include "TextRenderer.h"
#include "ResourceManager.h"

TextRenderer::TextRenderer() {
	//If Texture/Shader doesn't already exist in memory, then load it up
	if(ResourceManager::getShaderID("Text") == 0)
		ResourceManager::loadShader("shaders/Text_Shader.vs", "shaders/Text_Shader.fs", "Text");
	if (ResourceManager::getTextureID("Text") == 0)
		ResourceManager::loadTexture("fonts/Default.png", "Text");

	projection = glm::mat4(1);
	tilePosition = glm::vec2(0.0f, 0.0f);
	float vertices[] = {
		// positions          // colors           // texture coords
		0.3f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
		0.3f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-0.0f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
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
TextRenderer::~TextRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void TextRenderer::setAppropriateChar(const char ch) {
	//Characters found in the file in the fonts folder
	switch (ch)
	{
	case ' ': tilePosition = glm::vec2(0.0f, 5.0f);
		break;
	case '!': tilePosition = glm::vec2(1.0f, 5.0f);
		break;
	case '\"': tilePosition = glm::vec2(2.0f, 5.0f);
		break;
	case '#': tilePosition = glm::vec2(3.0f, 5.0f);
		break;
	case '$': tilePosition = glm::vec2(4.0f, 5.0f);
		break;
	case '%': tilePosition = glm::vec2(5.0f, 5.0f);
		break;
	case '&': tilePosition = glm::vec2(6.0f, 5.0f);
		break;
	case '\'': tilePosition = glm::vec2(7.0f, 5.0f);
		break;
	case '(': tilePosition = glm::vec2(8.0f, 5.0f);
		break;
	case ')': tilePosition = glm::vec2(9.0f, 5.0f);
		break;
	case '*': tilePosition = glm::vec2(10.0f, 5.0f);
		break;
	case '+': tilePosition = glm::vec2(11.0f, 5.0f);
		break;
	case ',': tilePosition = glm::vec2(12.0f, 5.0f);
		break;
	case '-': tilePosition = glm::vec2(13.0f, 5.0f);
		break;
	case '.': tilePosition = glm::vec2(14.0f, 5.0f);
		break;
	case '/': tilePosition = glm::vec2(15.0f, 5.0f);
		break;
	case '0': tilePosition = glm::vec2(0.0f, 4.0f);
		break;
	case '1': tilePosition = glm::vec2(1.0f, 4.0f);
		break;
	case '2': tilePosition = glm::vec2(2.0f, 4.0f);
		break;
	case '3': tilePosition = glm::vec2(3.0f, 4.0f);
		break;
	case '4': tilePosition = glm::vec2(4.0f, 4.0f);
		break;
	case '5': tilePosition = glm::vec2(5.0f, 4.0f);
		break;
	case '6': tilePosition = glm::vec2(6.0f, 4.0f);
		break;
	case '7': tilePosition = glm::vec2(7.0f, 4.0f);
		break;
	case '8': tilePosition = glm::vec2(8.0f, 4.0f);
		break;
	case '9': tilePosition = glm::vec2(9.0f, 4.0f);
		break;
	case ':': tilePosition = glm::vec2(10.0f, 4.0f);
		break;
	case ';': tilePosition = glm::vec2(11.0f, 4.0f);
		break;
	case '<': tilePosition = glm::vec2(12.0f, 4.0f);
		break;
	case '=': tilePosition = glm::vec2(13.0f, 4.0f);
		break;
	case '>': tilePosition = glm::vec2(14.0f, 4.0f);
		break;
	case '?': tilePosition = glm::vec2(15.0f, 4.0f);
		break;
	case '@': tilePosition = glm::vec2(0.0f, 3.0f);
		break;
	case 'A': tilePosition = glm::vec2(1.0f, 3.0f);
		break;
	case 'B': tilePosition = glm::vec2(2.0f, 3.0f);
		break;
	case 'C': tilePosition = glm::vec2(3.0f, 3.0f);
		break;
	case 'D': tilePosition = glm::vec2(4.0f, 3.0f);
		break;
	case 'E': tilePosition = glm::vec2(5.0f, 3.0f);
		break;
	case 'F': tilePosition = glm::vec2(6.0f, 3.0f);
		break;
	case 'G': tilePosition = glm::vec2(7.0f, 3.0f);
		break;
	case 'H': tilePosition = glm::vec2(8.0f, 3.0f);
		break;
	case 'I': tilePosition = glm::vec2(9.0f, 3.0f);
		break;
	case 'J': tilePosition = glm::vec2(10.0f, 3.0f);
		break;
	case 'K': tilePosition = glm::vec2(11.0f, 3.0f);
		break;
	case 'L': tilePosition = glm::vec2(12.0f, 3.0f);
		break;
	case 'M': tilePosition = glm::vec2(13.0f, 3.0f);
		break;
	case 'N': tilePosition = glm::vec2(14.0f, 3.0f);
		break;
	case 'O': tilePosition = glm::vec2(15.0f, 3.0f);
		break;
	case 'P': tilePosition = glm::vec2(0.0f, 2.0f);
		break;
	case 'Q': tilePosition = glm::vec2(1.0f, 2.0f);
		break;
	case 'R': tilePosition = glm::vec2(2.0f, 2.0f);
		break;
	case 'S': tilePosition = glm::vec2(3.0f, 2.0f);
		break;
	case 'T': tilePosition = glm::vec2(4.0f, 2.0f);
		break;
	case 'U': tilePosition = glm::vec2(5.0f, 2.0f);
		break;
	case 'V': tilePosition = glm::vec2(6.0f, 2.0f);
		break;
	case 'W': tilePosition = glm::vec2(7.0f, 2.0f);
		break;
	case 'X': tilePosition = glm::vec2(8.0f, 2.0f);
		break;
	case 'Y': tilePosition = glm::vec2(9.0f, 2.0f);
		break;
	case 'Z': tilePosition = glm::vec2(10.0f, 2.0f);
		break;
	case '[': tilePosition = glm::vec2(11.0f, 2.0f);
		break;
	case '\\': tilePosition = glm::vec2(12.0f, 2.0f);
		break;
	case ']': tilePosition = glm::vec2(13.0f, 2.0f);
		break;
	case '^': tilePosition = glm::vec2(14.0f, 2.0f);
		break;
	case '_': tilePosition = glm::vec2(15.0f, 2.0f);
		break;
	case '`': tilePosition = glm::vec2(0.0f, 1.0f);
		break;
	case 'a': tilePosition = glm::vec2(1.0f, 1.0f);
		break;
	case 'b': tilePosition = glm::vec2(2.0f, 1.0f);
		break;
	case 'c': tilePosition = glm::vec2(3.0f, 1.0f);
		break;
	case 'd': tilePosition = glm::vec2(4.0f, 1.0f);
		break;
	case 'e': tilePosition = glm::vec2(5.0f, 1.0f);
		break;
	case 'f': tilePosition = glm::vec2(6.0f, 1.0f);
		break;
	case 'g': tilePosition = glm::vec2(7.0f, 1.0f);
		break;
	case 'h': tilePosition = glm::vec2(8.0f, 1.0f);
		break;
	case 'i': tilePosition = glm::vec2(9.0f, 1.0f);
		break;
	case 'j': tilePosition = glm::vec2(10.0f, 1.0f);
		break;
	case 'k': tilePosition = glm::vec2(11.0f, 1.0f);
		break;
	case 'l': tilePosition = glm::vec2(12.0f, 1.0f);
		break;
	case 'm': tilePosition = glm::vec2(13.0f, 1.0f);
		break;
	case 'n': tilePosition = glm::vec2(14.0f, 1.0f);
		break;
	case 'o': tilePosition = glm::vec2(15.0f, 1.0f);
		break;
	case 'p': tilePosition = glm::vec2(0.0f, 0.0f);
		break;
	case 'q': tilePosition = glm::vec2(1.0f, 0.0f);
		break;
	case 'r': tilePosition = glm::vec2(2.0f, 0.0f);
		break;
	case 's': tilePosition = glm::vec2(3.0f, 0.0f);
		break;
	case 't': tilePosition = glm::vec2(4.0f, 0.0f);
		break;
	case 'u': tilePosition = glm::vec2(5.0f, 0.0f);
		break;
	case 'v': tilePosition = glm::vec2(6.0f, 0.0f);
		break;
	case 'w': tilePosition = glm::vec2(7.0f, 0.0f);
		break;
	case 'x': tilePosition = glm::vec2(8.0f, 0.0f);
		break;
	case 'y': tilePosition = glm::vec2(9.0f, 0.0f);
		break;
	case 'z': tilePosition = glm::vec2(10.0f, 0.0f);
		break;
	case '{': tilePosition = glm::vec2(11.0f, 0.0f);
		break;
	case '|': tilePosition = glm::vec2(12.0f, 0.0f);
		break;
	case '}': tilePosition = glm::vec2(13.0f, 0.0f);
		break;
	case '~': tilePosition = glm::vec2(14.0f, 0.0f);
		break;
	default: tilePosition = glm::vec2(15.0f, 0.0f);
		break;
	}
}
void TextRenderer::render(const std::string text, GLfloat posx, GLfloat posy, GLfloat scalex, GLfloat scaley, glm::vec3 color, GLfloat rotation) {
	this->projection = glm::translate(glm::mat4(1), glm::vec3(posx + scalex * text.length() / 4.0f, posy, 0.0f));
	this->projection = glm::rotate(projection, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	this->projection = glm::translate(projection, glm::vec3(-scalex*text.length() /4.0f, 0.0f, 0.0f));
	glm::vec3 transform = glm::vec3(scalex/4.0f, 0.0f, 0.0f);
	ResourceManager::bindTexture("Text");
	ResourceManager::bindShader("Text");

	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < text.length(); i++) {
		setAppropriateChar(text[i]);
		ResourceManager::setUniformMat4("Text", this->projection, "projection");
		projection = glm::translate(this->projection, transform);
		ResourceManager::setUniformVec2("Text", this->tilePosition, "tilePosition");
		ResourceManager::setUniformVec3("Text", color, "inColor");
		ResourceManager::setUniform1f("Text", scalex, "scalex");
		ResourceManager::setUniform1f("Text", scaley, "scaley");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}