#include "Renderer.h"


void Renderer::clear() const
{
	glClearColor(0.2f, 0.5f, 0.8f, 1.0f);  // Defines the color that clears the screen, also sets the state
	glClear(GL_COLOR_BUFFER_BIT);          // Clears the colour buffer, uses current state to get clearing color
}

void Renderer::draw(const VertexArray& VAO, const ElementBuffer& EBO, const Shader& shader) const
{
	shader.use();

	shader.setUniform<float>("time", glfwGetTime());

	VAO.bind();
	glDrawElements(GL_TRIANGLES, EBO.getIndiceCount(), GL_UNSIGNED_INT, NULL);
}
