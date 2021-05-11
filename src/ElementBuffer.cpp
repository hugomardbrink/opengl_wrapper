#include "ElementBuffer.h"

/**
 * Allocates GPU-resource to the element buffer, generates opengl ID and loads indices. 
 * @param data The indices that gets loaded to the element buffer
 * @param count The size of the indice array
 */
ElementBuffer::ElementBuffer(const uint32_t* data, uint32_t size) 
{
	glGenBuffers(1, &m_rendererID); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);  
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
	m_indiceCount = size / sizeof(uint32_t);
}

/**
 * Deallocates the element buffers GPU-resource 
 */
ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}

/**
 * Bind the selected buffer to the internal opengl element buffer
 */
void ElementBuffer::bind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); // Bind the vertex buffer to opengl
}

 /**
  * Unbinds the opengl internal element buffer from buffers
  */
void ElementBuffer::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

/**
 * @return How many indices are loaded to the element buffer
 */
uint32_t ElementBuffer::getIndiceCount() const
{
	return m_indiceCount;
}
