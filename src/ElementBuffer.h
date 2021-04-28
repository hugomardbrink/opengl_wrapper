#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>

/**
 * Handles element buffer by allocating resources and loading indices and storing indice information
 */
class ElementBuffer {
public:
	ElementBuffer(const uint32_t* data, uint32_t size);
	~ElementBuffer();
	void bind() const;
	void unbind() const;
	uint32_t getIndiceCount() const;
private:
	uint32_t rendererID;
	uint32_t indiceCount;
};

