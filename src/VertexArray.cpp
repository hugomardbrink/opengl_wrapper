#include "VertexArray.h"
#include "BufferLayout.h"

/**
 * Allocates a GPU-resource for a vertex array
 */
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
	glBindVertexArray(rendererID);
}

/**
 * Deallocates the GPU-resource for the current vertex array
 */
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

/**
 * Adds a vertex buffer and a stride-layout for the buffer
 * @param VBO The vertexbuffer to add
 * @param layout The layout to traverse the buffer
 */
void VertexArray::addBuffer(const VertexBuffer& VBO, const BufferLayout& layout)
{
	VBO.bind();
	const auto& elements = layout.getElements();

	for (uint32_t i = 0; i < elements.size(); i++) 
	{
		const auto& element = elements[i];

		glVertexAttribPointer(i, element.count, element.type, element.normalized, 
			layout.getStride() * sizeof(element.type), (const void*)element.offset); // location 0, set attributes of the pos, set type, no normalizing, set stride distance size.
		
		glEnableVertexAttribArray(i);   // Enable vertex attributes, vertex attribute 0 is now associated with its vertex data
	}
	
}

/**
 * Bind the vertex array to the current opengl vertex array
 */
void VertexArray::bind() const
{
	glBindVertexArray(rendererID);
}

/**
 * Unbind current vertex array from opengl
 */
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
