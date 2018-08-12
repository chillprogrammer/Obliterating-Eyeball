#version 330 core

out vec4 FragColor;  
in vec2 TexCoord;
in float total_frames;

uniform vec3 inColor;
uniform sampler2D ourTexture;
uniform float alpha;

void main()
{
    vec2 subTexCoord = TexCoord + vec2(0.5f / total_frames, 1.0f);
    vec4 img = texture2D(ourTexture, TexCoord + vec2(0.5f / total_frames, 0.0f));
    FragColor = vec4(inColor, alpha)*img;
}