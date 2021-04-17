#include "VertexArray.h"
#include "BufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
	glBindVertexArray(rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::addBuffer(const BufferLayout& layout)
{
	const auto& elements = layout.getElements();

	for (uint32_t i = 0; i < elements.size(); i++) 
	{
		const auto& element = elements[i];

		glVertexAttribPointer(i, element.count, element.type, element.normalized, 
			layout.getStride() * sizeof(element.type), (const void*)element.offset); // location 0, set attributes of the pos, set type, no normalizing, set stride distance size.
		
		glEnableVertexAttribArray(i);   // Enable vertex attributes, vertex attribute 0 is now associated with its vertex data
	}
	
}

void VertexArray::bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
