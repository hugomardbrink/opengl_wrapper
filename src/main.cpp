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
#include "Camera.h"
#include "KeyInput.h"



float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

/**
 * Processes inputs from the keyboard
 * @note should be event triggers
 */
void processInput(KeyInput& keyInput, GLFWwindow* glfwWindow, Camera& camera)
{
    // Checks if escape key is pressed, then closes window
    if (keyInput.isPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(glfwWindow, true);

    if (keyInput.isPressed(GLFW_KEY_Z))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (keyInput.isPressed(GLFW_KEY_X))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
    
    glm::vec3 cameraUp(0.0f, 0.1f, 0.0f);

	const float cameraSpeed = 10.0f * deltaTime; // adjust accordingly
    if (keyInput.isPressed(GLFW_KEY_W))
        camera.moveAlongZ(cameraSpeed);
    if (keyInput.isPressed(GLFW_KEY_S))
        camera.moveAlongZ(-cameraSpeed);
    if (keyInput.isPressed(GLFW_KEY_A))
        camera.moveAlongX(-cameraSpeed);
    if (keyInput.isPressed(GLFW_KEY_D))
        camera.moveAlongX(cameraSpeed);
    if (keyInput.isPressed(GLFW_KEY_SPACE))
		camera.moveAlongY(cameraSpeed);
    if (keyInput.isPressed(GLFW_KEY_LEFT_SHIFT))
		camera.moveAlongY(-cameraSpeed);


}





int32_t main()
{
    Window window;
	Renderer renderer;

    // Vertices for rectangles: position, colour and texture position
    /*float vertices[] =
    {    // Position            // Colour            // Texture Position
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // top left
    }; */


	float vertices[] = 
    {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


    glm::vec3 cubePositions[] =
    {
       glm::vec3(0.0f, 0.0f, 0.0f),
	   glm::vec3(-1.7f,  3.0f, -7.5f),
       glm::vec3(2.8f, 2.0f, -7.0f),
       glm::vec3(2.4f, -0.4f, -3.5f),
       glm::vec3(-1.3f, -1.5f, -2.5f),
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

    /*
    layout.push<float>(3); // Vertices
    layout.push<float>(3); // Colors
    layout.push<float>(2); // Texture
    */

    layout.push<float>(3); // Vertices
    layout.push<float>(2); // Texture



    VAO.addBuffer(VBO, layout);

    Texture2D oceanTexture("./assets/textures/ocean_texture.jpg");
    Texture2D islandTexture("./assets/textures/island_texture.png");

    shader.use();
    shader.setUniform<int>("oceanTexture", 0);
    oceanTexture.bind(0);
    shader.setUniform<int>("islandTexture", 1);
    islandTexture.bind(1);


    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    KeyInput keyInput(window.getGlfwWindow());


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    shader.use();
    shader.setUniform<glm::mat4>("projection", projection);


    renderer.enableDepthTesting();
    while (!window.windowClosing())
    {
        /*  INPUTS  */
        processInput(keyInput, window.getGlfwWindow(), camera);

        /*  RENDERING  */

        renderer.clear(glm::vec4(0.2f, 0.5f, 0.8f, 1.0f));

        /*
		const float radius = 20.0f;
        camera.setPosX(sin(glfwGetTime())* radius);
        camera.setPosZ(cos(glfwGetTime())* radius);
        */
        glm::mat4 view = camera.getLookAt();
        shader.setUniform<glm::mat4>("view", view);

		for (uint32_t i = 0; i < 5; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
            float angle = 40.0f * i;
            if (i % 2) model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            else model = glm::rotate(model, (float)-glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setUniform<glm::mat4>("model", model);
            renderer.draw(VAO, EBO, shader);
		}

        /*  CHECK EVENTS AND SWAP BUFFER  */

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;           
}


