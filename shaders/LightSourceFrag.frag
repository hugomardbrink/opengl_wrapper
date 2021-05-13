#version 330 core
//uniform sampler2D oceanTexture;
//uniform sampler2D islandTexture;

uniform vec3 lightColour;

out vec4 FragColor; 

  
void main() 
{
    FragColor = vec4(lightColour, 1.0);
}