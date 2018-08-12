#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 inColor;
uniform sampler2D ourTexture;
uniform float alpha;
uniform vec2 pupil_pos;
uniform vec2 pupil_scale;

void main()
{
    vec4 img = texture2D(ourTexture, TexCoord);
    FragColor = vec4(inColor, alpha)*img;

   /**
    * Ellipse equation =  (x/a)2 + (y/b)2 = 1 
    *     a = horizontal radius
    *     b = vertical   radius 
    */
    

    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    float e1 =  ( TexCoord.x - pupil_pos.x ) / ( pupil_scale.x );
    float e2 =  ( TexCoord.y - pupil_pos.y ) / ( pupil_scale.y );
    float d  = (e1 * e1) + (e2 * e2);
    if( d > 1 ) {
        FragColor = vec4(inColor, alpha)*img;
    } 
}