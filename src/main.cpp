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


	float vertices[] = {
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
    layout.push<float>(3);
    layout.push<float>(2);



    VAO.addBuffer(VBO, layout);

    Texture2D oceanTexture("./assets/textures/ocean_texture.jpg");
    Texture2D islandTexture("./assets/textures/island_texture.png");

    shader.use();
    shader.setUniform<int>("oceanTexture", 0);
    oceanTexture.bind(0);
    shader.setUniform<int>("islandTexture", 1);
    islandTexture.bind(1);



    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);



    shader.use();
    shader.setUniform<glm::mat4>("view", view);
    shader.setUniform<glm::mat4>("projection", projection);


    renderer.enableDepthBuffer();
    while (!window.windowClosing())
    {
        /*  INPUTS  */
        window.processInput();

        /*  RENDERING  */

        renderer.clear(glm::vec4{0.2f, 0.5f, 0.8f, 1.0f});

        // Create a matrix that scales and rotates
        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(1.25f, 1.25f, 1.25f));


		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.setUniform<glm::mat4>("model", model);

        shader.setUniform<glm::mat4>("rotationMatrix", trans);

        renderer.draw(VAO, EBO, shader);


        /*  CHECK EVENTS AND SWAP BUFFER  */

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;           
}
