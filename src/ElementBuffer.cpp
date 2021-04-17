#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const uint32_t* data, uint32_t count) 
{
	glGenBuffers(1, &rendererID); // Generate buffer ID for a element buffer that is getting sent to GPU and decides what vertices to draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);  // Bind our Element buffer to the opengl element array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW); // Load our indecies to the element buffer
	indiceCount = count / sizeof(uint32_t);
	
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void ElementBuffer::bind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); // Bind the vertex buffer to opengl
}

void ElementBuffer::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Bind the vertex buffer to opengl
}

uint32_t ElementBuffer::getIndiceCount() const
{
	return indiceCount;
}
