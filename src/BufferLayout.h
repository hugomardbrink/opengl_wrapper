#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <assert.h>

/**
 * Encapsulates the data needed to configure future vertex buffer-traversing
 */
struct BufferElement {
	uint32_t type;
	uint32_t count;
	uint8_t normalized;
	uint32_t offset;
};


/**
 * Stores a layout on how to traverse a buffer
 */
class BufferLayout{
public:
	BufferLayout();
	uint32_t getStride() const;
	std::vector<BufferElement> getElements() const;
	template <typename T> void push(uint32_t count);

private:
	std::vector<BufferElement> elements;
	uint32_t stride;
	uint32_t offsetStart;
};

