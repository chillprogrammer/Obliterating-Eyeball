#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 inColor;
uniform sampler2D ourTexture;
uniform float alpha;

void main()
{
    vec4 img = texture2D(ourTexture, TexCoord);
    FragColor = vec4(inColor, alpha)*img;
}