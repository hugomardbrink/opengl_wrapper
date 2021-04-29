#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Window.h"
#include "Texture2D.h"

// This is to check if specific input are pressed in this window
void processInput(GLFWwindow* window);

int32_t main()
{

    Window window;

    // Vertices for rectangles: position, colour and texture position
    float vertices[] =
    {    // Position            // Colour            // Texture Position
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // top left
    };

    // Indices for rectangle
    uint32_t indices[] =
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    Shader shader("./shaders/VertexShader.vert", "./shaders/FragmentShader.frag");

    VertexArray VAO;
    VertexBuffer VBO(vertices, sizeof(vertices));
    ElementBuffer EBO(indices, sizeof(indices));

    BufferLayout layout;
    layout.push<float>(3); // Vertices
    layout.push<float>(3); // Colors
    layout.push<float>(2); // Texture

    VAO.addBuffer(VBO, layout);

    Texture2D oceanTexture("./assets/textures/ocean_texture.jpg");
    Texture2D islandTexture("./assets/textures/island_texture.png");

    shader.use();
    shader.setUniform<int>("oceanTexture", 0);
    oceanTexture.bind(0);
    shader.setUniform<int>("islandTexture", 1);
    islandTexture.bind(1);


    Renderer renderer;
    while (!window.windowClosing())
    {
        /*  INPUTS  */
        processInput(window.getGlfwWindow());

        /*  RENDERING  */

        renderer.clear(glm::vec4{ 0.2f, 0.5f, 0.8f, 1.0f });

        // Create a matrix that scales and rotates
        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(1.25f, 1.25f, 1.25f));

        shader.setUniform<glm::mat4>("rotationMatrix", trans);

        renderer.draw(VAO, EBO, shader);


        /*  CHECK EVENTS AND SWAP BUFFER  */

        // Swap pixels with 2D colour buffer
        window.swapBuffers();
        // Checks for event triggers
        window.pollEvents();
    }

    // Deallocates all glfw resources
    glfwTerminate();   
    return 0;           
}

void processInput(GLFWwindow* window) 
{
    // Checks if escape key is pressed, then closes window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  
        glfwSetWindowShouldClose(window, true);             

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
