#include "Renderer.h"

/**
 * Clears window with specified colour
 * @param colour The colour vector that clears the screen
 * @note Depth buffer bit should be cleared only when enabled
 */
void Renderer::clear(glm::vec4 colour) const
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);  // Sets state and its colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clears the colour buffer with states current colour
}

/**
 * Draws the window each frame
 * @param VAO The vertex array with bound vertex buffer and strife-layour
 * @param shader The shader used when drawing said vertices
 * @note should element buffer really be here?
 */
void Renderer::draw(const VertexArray& VAO, const Shader& shader) const
{
	shader.use();

	VAO.bind();
	//glDrawElements(GL_TRIANGLES, EBO.getIndiceCount(), GL_UNSIGNED_INT, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * Enables depth testing
 */
void Renderer::enableDepthTesting()
{
	glEnable(GL_DEPTH_TEST);
}

/**
 * Disables depth testing
 */
void Renderer::disableDepthTesting()
{
	glDisable(GL_DEPTH_TEST);
}

