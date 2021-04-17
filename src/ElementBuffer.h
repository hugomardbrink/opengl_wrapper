#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>


class ElementBuffer {
public:
	ElementBuffer(const uint32_t* data, uint32_t count);
	~ElementBuffer();
	void bind() const;
	void unbind() const;
	uint32_t getIndiceCount() const;
private:
	uint32_t rendererID;
	uint32_t indiceCount;
};

