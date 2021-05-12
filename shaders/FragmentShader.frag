#version 330 core
in vec2 TexCoord;

//uniform sampler2D oceanTexture;
//uniform sampler2D islandTexture;

uniform vec3 objectColour;
uniform vec3 lightColour;

out vec4 FragColor; 

  
void main() 
{
    FragColor = vec4(lightColour * objectColour, 1.0);
}