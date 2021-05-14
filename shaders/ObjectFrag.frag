#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D oceanTexture;
uniform sampler2D islandTexture;

uniform vec3 objectColour;
uniform vec3 lightColour;

uniform vec3 lightPos;
uniform vec3 viewPos;

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
            
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;  

    vec3 result = (ambient + diffuse + specular) * objectColour;
    FragColor = mix(texture(oceanTexture, texCoord), texture(islandTexture, texCoord), texture(islandTexture, texCoord).a) *  vec4(result, 1.0);
}