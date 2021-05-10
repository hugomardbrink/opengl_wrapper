#pragma once
#include <glad/glad.h> 
#include <stdint.h>

#include "BufferLayout.h"
#include "VertexBuffer.h"

/**
 * A vertex array for adding vertex buffers and binding to opengl
 */
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void addBuffer(const VertexBuffer& VBO, const BufferLayout& layout);
	void bind() const;
	void unbind() const;
private:
	uint32_t m_rendererID;

};

