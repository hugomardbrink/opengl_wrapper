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
#include "input.h"



float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = 400, lastY = 300;

glm::vec3 direction;
glm::vec3 eulerAngles(0.0f, -89.0f, 0.0f);

/**
 * Processes inputs from the keyboard
 * @note should be event triggers
 */
void processInput(Input& input, GLFWwindow* glfwWindow, Camera& camera)
{
    // Checks if escape key is pressed, then closes window
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(glfwWindow, true);

    if (input.isKeyPressed(glfwWindow, GLFW_KEY_Z))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (input.isKeyPressed(glfwWindow, GLFW_KEY_X))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
    
    glm::vec3 cameraUp(0.0f, 0.1f, 0.0f);

	const float cameraSpeed = 10.0f * deltaTime; // adjust accordingly
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_W))
        camera.moveAlongZ(cameraSpeed);
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_S))
        camera.moveAlongZ(-cameraSpeed);
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_A))
        camera.moveAlongX(-cameraSpeed);
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_D))
        camera.moveAlongX(cameraSpeed);
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_SPACE))
		camera.moveAlongY(cameraSpeed);
    if (input.isKeyPressed(glfwWindow, GLFW_KEY_LEFT_SHIFT))
		camera.moveAlongY(-cameraSpeed);




}

void mouse_input(Window& window, Input& input)
{
    glm::vec2 cursorPosition = input.getMousePosition(window.getGlfwWindow());

	float xoffset = cursorPosition.x - lastX;
	float yoffset = lastY - cursorPosition.y; // reversed since y-coordinates range from bottom to top
	lastX = cursorPosition.x;
	lastY = cursorPosition.y;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;


	eulerAngles.y += xoffset;
	eulerAngles.x += yoffset;


	if (eulerAngles.x > 89.0f)
        eulerAngles.x = 89.0f;
	if (eulerAngles.x < -89.0f)
        eulerAngles.x = -89.0f;


	direction.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	direction.y = sin(glm::radians(eulerAngles.x));
	direction.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));

}

int32_t main()
{
    Window window;
	Renderer renderer;
    Input input;

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
	BufferLayout layout;

    ElementBuffer EBO(indices, sizeof(indices));




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


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();
    shader.setUniform<glm::mat4>("projection", projection);


    input.disableCursor(window.getGlfwWindow());
   

    renderer.enableDepthTesting();
    while (!window.windowClosing())
    {
        /*  INPUTS  */
        processInput(input, window.getGlfwWindow(), camera);
        mouse_input(window, input);

        /*  RENDERING  */

        renderer.clear(glm::vec4(0.2f, 0.5f, 0.8f, 1.0f));


        camera.setFront(glm::normalize(direction));

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


