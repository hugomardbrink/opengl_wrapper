#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>
#include "BufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void addBuffer(const BufferLayout& layout);
	void bind() const;
	void unbind() const;
private:
	uint32_t rendererID;

};

