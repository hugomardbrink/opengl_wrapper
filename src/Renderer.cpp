#include "Renderer.h"

/**
 * Clears window with specified colour
 * @param colour The colour that clears the screen
 */
void Renderer::clear(glm::vec4 colour) const
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);  // Defines the color that clears the screen, also sets the state
	glClear(GL_COLOR_BUFFER_BIT);          // Clears the colour buffer, uses current state to get clearing color
}

void Renderer::draw(const VertexArray& VAO, const ElementBuffer& EBO, const Shader& shader) const
{
	shader.use();

	shader.setUniform<float>("time", glfwGetTime());

	VAO.bind();
	glDrawElements(GL_TRIANGLES, EBO.getIndiceCount(), GL_UNSIGNED_INT, NULL);
}
