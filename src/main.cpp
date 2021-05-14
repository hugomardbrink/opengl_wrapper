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
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	};

	

    glm::vec3 cubePositions[] =
    {
       glm::vec3(0.0f, 0.0f, 0.0f),
	   glm::vec3(-3.0f,  2.0f, -2.5f),
    };


    Shader objectShader("./shaders/ObjectVertex.vert", "./shaders/ObjectFrag.frag");
    Shader lightSourceShader("./shaders/LightSourceVertex.vert", "./shaders/LightSourceFrag.frag");

    VertexArray objectVAO, lightVAO;
	VertexBuffer VBO(vertices, sizeof(vertices));
	BufferLayout layout;

    layout.push<float>(3); // Vertices
    layout.push<float>(3); // Normals
	layout.push<float>(2); // Textures

    objectVAO.addBuffer(VBO, layout);
    lightVAO.addBuffer(VBO, layout);
	

	Texture2D oceanTexture("./assets/textures/ocean_texture.jpg");
	Texture2D islandTexture("./assets/textures/island_texture.png");


	objectShader.use();
	objectShader.setUniform<int>("oceanTexture", 0);
	oceanTexture.bind(0);
	objectShader.setUniform<int>("islandTexture", 1);
	islandTexture.bind(1);


    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    input.disableCursor(window.getGlfwWindow());

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    glm::vec3 objectColour(1.0f, 1.0f, 1.0f);


    objectShader.use();
	objectShader.setUniform<glm::mat4>("projection", projection);
	objectShader.setUniform<glm::vec3>("objectColour", objectColour);
	objectShader.setUniform<glm::vec3>("lightPos", cubePositions[1]);
	lightSourceShader.use();
	lightSourceShader.setUniform<glm::mat4>("projection", projection);


 
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
		lightColour = glm::vec3(1.0f, 1.0f, 1.0f);




		objectShader.use();
		objectShader.setUniform<glm::vec3>("lightColour", lightColour);
		objectShader.setUniform<glm::mat4>("view", view);

		const float radius = 10.0f;
		float lightX = sin(glfwGetTime()) * radius;
		float lightZ = cos(glfwGetTime()) * radius;


		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[0]);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		objectShader.setUniform<glm::mat4>("model", model);
		objectShader.setUniform<glm::vec3>("viewPos", camera.getPosition());
		renderer.draw(objectVAO, objectShader);



		lightSourceShader.use();
		lightSourceShader.setUniform<glm::vec3>("lightColour", lightColour);
		lightSourceShader.setUniform<glm::mat4>("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[1]);
		lightSourceShader.setUniform<glm::mat4>("model", model);
		renderer.draw(lightVAO, lightSourceShader);




        /*  CHECK EVENTS AND SWAP BUFFER  */

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;           
}


