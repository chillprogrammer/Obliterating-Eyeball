#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec2 tileDims;

uniform vec3 inColor;
uniform sampler2D ourTexture;
uniform float mouseHovering;

void main()
{
    vec2 subTexCoord = TexCoord + vec2(0.5f / tileDims.x, 0.5f / tileDims.y);
    vec4 img = texture2D(ourTexture, TexCoord + vec2(0.5f / tileDims.x, 0.5f / tileDims.y));
    FragColor = vec4(inColor, 1.0)*img;

    if(mouseHovering == 1.0f) {
        FragColor = vec4(inColor, 1.0)*img*vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }

    //if(detail > 0.0) {
    //    FragColor = vec4(inColor, 1.0)*img*vec4(1.0f, 0.41f, 0.71f, 1.0f);
    //}

}