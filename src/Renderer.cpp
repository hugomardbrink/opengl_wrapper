#include "Renderer.h"

/**
 * Clears window with specified colour
 * @param colour The colour vector that clears the screen
 */
void Renderer::clear(glm::vec4 colour) const
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);  // Sets state and its colour
	glClear(GL_COLOR_BUFFER_BIT);						   // Clears the colour buffer with states current colour
}

/**
 * Draws the window each frame
 * @param VAO The vertex array with bound vertex buffer and strife-layour
 * @param EBO The element buffer used for checking indices
 * @param shader The shader used when drawing said vertices
 */
void Renderer::draw(const VertexArray& VAO, const ElementBuffer& EBO, const Shader& shader) const
{
	shader.use();

	shader.setUniform<float>("time", glfwGetTime());

	VAO.bind();
	glDrawElements(GL_TRIANGLES, EBO.getIndiceCount(), GL_UNSIGNED_INT, NULL);
}

