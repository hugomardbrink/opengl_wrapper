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
#include "Input.h"



float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = 400, lastY = 300;

glm::vec3 direction;
glm::vec3 eulerAngles(0.0f, -89.0f, 0.0f);

/**
 * Processes inputs from the keyboard
 * @note should be event triggers
 */
void keyboard_input(Window& window, Input& input, Camera& camera)
{
    // Checks if escape key is pressed, then closes window
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window.getGlfwWindow(), true);

    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_Z))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_X))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
    
    glm::vec3 cameraUp(0.0f, 0.1f, 0.0f);

	const float cameraSpeed = 10.0f * deltaTime; // adjust accordingly
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_W))
        camera.moveAlongZ(cameraSpeed);
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_S))
        camera.moveAlongZ(-cameraSpeed);
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_A))
        camera.moveAlongX(-cameraSpeed);
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_D))
        camera.moveAlongX(cameraSpeed);
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_SPACE))
		camera.moveAlongY(cameraSpeed);
    if (input.isKeyPressed(window.getGlfwWindow(), GLFW_KEY_LEFT_SHIFT))
		camera.moveAlongY(-cameraSpeed);




}

void mouse_input(Window& window, Input& input, Camera& camera)
{
    glm::vec2 cursorPosition = input.getMousePosition(window.getGlfwWindow());

	float deltaX = cursorPosition.x - lastX;
	float deltaY = lastY - cursorPosition.y; // reversed since y-coordinates range from bottom to top
	lastX = cursorPosition.x;
	lastY = cursorPosition.y;

	const float sensitivity = 0.1f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;


	eulerAngles.y += deltaX;
	eulerAngles.x += deltaY;


	if (eulerAngles.x > 89.0f)
        eulerAngles.x = 89.0f;
	if (eulerAngles.x < -89.0f)
        eulerAngles.x = -89.0f;


    camera.rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z);

}

int32_t main()
{
    Window window;
	Renderer renderer;
    Input input;


	float vertices[] = 
	{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


    glm::vec3 cubePositions[] =
    {
       glm::vec3(0.0f, 0.0f, 0.0f),
	   glm::vec3(-1.0f,  2.0f, -2.5f),
    };


    Shader cubeShader("./shaders/VertexShader.vert", "./shaders/FragmentShader.frag");
    Shader lightingShader("./shaders/VertexShader.vert", "./shaders/LightSourceShader.frag");

    VertexArray objectVAO, lightVAO;
	VertexBuffer VBO(vertices, sizeof(vertices));
	BufferLayout layout;

    layout.push<float>(3); // Vertices
    layout.push<float>(3); // Normals

    objectVAO.addBuffer(VBO, layout);
    lightVAO.addBuffer(VBO, layout);

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    input.disableCursor(window.getGlfwWindow());

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    glm::vec3 objectColour(1.0f, 0.5f, 0.31f);


    cubeShader.use();
    cubeShader.setUniform<glm::mat4>("projection", projection);
    cubeShader.setUniform<glm::vec3>("objectColour", objectColour);
    lightingShader.use();
    lightingShader.setUniform<glm::mat4>("projection", projection);


 
    glm::mat4 model;
    glm::vec3 lightColour;
    renderer.enableDepthTesting();
    while (!window.windowClosing())
    {
        /*  INPUTS  */
        keyboard_input(window, input, camera);
        mouse_input(window, input, camera);

        /*  RENDERING  */

        renderer.clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        glm::mat4 view = camera.getLookAt();
        lightColour = glm::vec3(1.0f, 1.0f, 1.0f) * (float) sin(glfwGetTime());




		cubeShader.use();
		cubeShader.setUniform<glm::vec3>("lightColour", lightColour);
		cubeShader.setUniform<glm::mat4>("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[0]);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		cubeShader.setUniform<glm::mat4>("model", model);
		renderer.draw(objectVAO, cubeShader);



		lightingShader.use();
		lightingShader.setUniform<glm::vec3>("lightColour", lightColour);
		lightingShader.setUniform<glm::mat4>("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[1]);
		lightingShader.setUniform<glm::mat4>("model", model);
		renderer.draw(lightVAO, lightingShader);




        /*  CHECK EVENTS AND SWAP BUFFER  */

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;           
}


