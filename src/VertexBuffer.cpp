#include "VertexBuffer.h"

/**
 * Allocates a GPU-resource and loads vertices in the created buffer
 * @param data The vertices that gets loaded
 * @param size The sice of the verice-array that gets loaded
 */
VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
	glGenBuffers(1, &rendererID); 
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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