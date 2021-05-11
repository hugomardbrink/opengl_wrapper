#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>

/**
 * Handles a vertex buffer and handles its storage of vertices
 */
class VertexBuffer {
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();
	void bind() const;
	void unbind() const;
private:
	uint32_t m_rendererID;
};

