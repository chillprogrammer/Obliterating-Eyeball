#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texPos;

out vec3 ourColor;
out vec2 TexCoord;
out float total_frames;

uniform float total_animation_frames;
uniform float animation_frame;
uniform mat4 projection;
uniform mat4 model;
uniform float scalex;
uniform float scaley;

void main()
{
    gl_Position = projection * model * vec4((scalex * aPos.x), (scaley * aPos.y), 0.0, 1.0);
    TexCoord = vec2((texPos.x + animation_frame)*(1.0f/total_animation_frames) - 0.5f/total_animation_frames, texPos.y);
	ourColor = aColor;
	total_frames = total_animation_frames;
}



