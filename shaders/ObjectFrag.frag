#version 330 core
in vec3 Normal;
in vec3 FragPos;

//uniform sampler2D oceanTexture;
//uniform sampler2D islandTexture;

uniform vec3 objectColour;
uniform vec3 lightColour;

uniform vec3 lightPos;

out vec4 FragColor; 

  
void main() 
{

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;
            
    vec3 result = (ambient + diffuse) * objectColour;
    FragColor = vec4(result, 1.0);
}