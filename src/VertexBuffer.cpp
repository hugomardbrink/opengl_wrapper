#include "VertexBuffer.h"

/**
 * Allocates a GPU-resource and loads vertices in the created buffer
 * @param data The vertices that gets loaded
 * @param size The sice of the verice-array that gets loaded
 */
VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
	glGenBuffers(1, &rendererID); // Generate buffer ID for a vertex buffer that is getting sent to GPU
	glBindBuffer(GL_ARRAY_BUFFER, rendererID); // Bind the vertex buffer to opengl
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // Load our vertices array to the buffer to a static drawing config
}

/**
 * Deallocates the GPU-resource		
 */
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &rendererID);
}

/**
 * Bind the vertex buffer to opengl current vertex buffer
 */
void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, rendererID); // Bind the vertex buffer to opengl
}

/**
 * Unbinds selected vertex buffer from opengl
 */
void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Bind the vertex buffer to opengl
}