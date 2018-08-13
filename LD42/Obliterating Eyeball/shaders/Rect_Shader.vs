#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texPos;

out vec2 TexCoord;

uniform mat4 model;
uniform float scalex;
uniform float scaley;

void main()
{
    gl_Position = model * vec4((scalex * aPos.x), (scaley * aPos.y), 0.0, 1.0);
	TexCoord = texPos;
}