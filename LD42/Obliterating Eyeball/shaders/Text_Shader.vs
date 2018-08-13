#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texPos;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 tilePosition;
uniform mat4 projection;
uniform float scalex;
uniform float scaley;

void main()
{
    gl_Position = projection * vec4((scalex * aPos.x), (scaley * aPos.y), 0.0, 1.0);
    ourColor = aColor;
	TexCoord = vec2((texPos.x + tilePosition.x)*(1.0f/16.0) - 0.5f/16.0, (texPos.y + tilePosition.y)*(1.0f/6.0) - 0.5f/6.0);

}