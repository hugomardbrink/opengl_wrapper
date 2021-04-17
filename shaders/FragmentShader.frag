#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D oceanTexture;
uniform sampler2D islandTexture;
  
void main() 
{
    FragColor = mix(texture(oceanTexture, TexCoord), texture(islandTexture, TexCoord), texture(islandTexture, TexCoord).a); // * vec4(ourColor, 1.0);
}