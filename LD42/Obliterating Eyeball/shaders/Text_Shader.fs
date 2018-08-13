#version 330 core
out vec4 FragColor;
  
//in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 inColor;
uniform sampler2D ourTexture;

void main()
{
    vec4 img = texture2D(ourTexture, TexCoord + vec2(0.5f / 16, 0.5f / 6));
    FragColor = vec4(inColor, 1.0)*img;
}