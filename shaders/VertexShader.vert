#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 2) in vec3 aColor; // the color variable has attribute position 1
layout (location = 1) in vec2 aTexCoord; // the texture has attribute position 2
  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform mat4 rotationMatrix;

out vec3 ourColor; // output a color to the fragment shader
out vec2 TexCoord;

void main() 
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

}       