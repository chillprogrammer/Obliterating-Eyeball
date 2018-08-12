#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 backColor;
uniform vec3 borderColor;
uniform float border_x;
uniform float border_y;

void main()
{
    float border_width = 0.01;
    float maxX = 1.0 - border_x;
    float minX = border_x;
    float maxY = 1.0 - border_y;
    float minY = border_y;

    if(TexCoord.x > maxX || TexCoord.x < border_x || TexCoord.y > maxY || TexCoord.y < border_y) {
        FragColor = vec4(borderColor, 1.0);
    }
    else {     
        FragColor = vec4(backColor, 1.0);
    }
}