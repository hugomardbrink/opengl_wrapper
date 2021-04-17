#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdint.h>

#include "stb_image.h"
    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture2D.h"



constexpr uint32_t HEIGHT = 600;
constexpr uint32_t WIDTH = 800;
constexpr uint32_t MAJOR_VER = 3;
constexpr uint32_t MINOR_VER = 3;
const     char*    WINDOW_NAME = "Window";

// When the user resizes window this function adjusts the openGL dimensions
void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height);
// This is to check if specific input are pressed in this window
void processInput(GLFWwindow* window);

GLFWwindow* initOpengl(int32_t height, int32_t width, int32_t majorVersion, int32_t minorVersion, const char* name);


int32_t main() 
{

    GLFWwindow* window = initOpengl(HEIGHT, WIDTH, MAJOR_VER, MINOR_VER, WINDOW_NAME);

    float vertices[] = 
    {    // Position            // Colour            // Texture Position
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // top left
    };

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
    layout.push<float>(3, 0); // Vertices
    layout.push<float>(3, 3); // Colors
    layout.push<float>(2, 6); // Texture

    VAO.addBuffer(layout);

    Texture2D oceanTexture("./assets/ocean_texture.jpg", GL_RGB);
    Texture2D islandTexture("./assets/island_texture.png", GL_RGBA);

    shader.use();
    shader.setUniform<int>("oceanTexture", 0);
	oceanTexture.bind(0);
    shader.setUniform<int>("islandTexture", 1);
    islandTexture.bind(1);

    Renderer renderer;
	while (!glfwWindowShouldClose(window)) {
		/*  INPUTS  */
		processInput(window);  // Check if any inputs are pressed

		/*  RENDERING  */

		renderer.clear();

		glm::mat4 trans(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(1.25f, 1.25f, 1.25f));

        shader.setUniform<glm::mat4>("rotationMatrix", trans);

        renderer.draw(VAO, EBO, shader);
	/*  CHECK EVENTS AND SWAP BUFFER  */
		glfwSwapBuffers(window);       // Checks if any events are triggered, updates window state and calls corresponding functions
		glfwPollEvents();              // This will swap each pixel with corresponding color from 2D buffer
	}

    glfwTerminate();    // This will clean up all the allocated glfw resources
    return 0;           // Exit application
}

void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // Checks if the escape key is pressed in the current window
        glfwSetWindowShouldClose(window, true);             // Close said window if condition is met

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height) 
{
    glViewport(0, 0, width, height);   // Resizes window to fit new resize
}

GLFWwindow* initOpengl(int32_t height, int32_t width, int32_t majorVersion, int32_t minorVersion, const char* name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);    // Using version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   // Core-profile, skip backward-compatibility features

    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);     // Create window for object

    // Window creation fails if the address is 0
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window); // Set the created windows context on the calling thread

    // If compiling on wrong OS, exit program
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();    // This will clean up all the allocated glfw resources
        return NULL;
    }

    // Tells openGL the rendering dimensions in respect to the window, (0,0) is bottom left corner
    glViewport(0, 0, width, height);

    // GLFW will use our framebuffer size callback whenever the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}