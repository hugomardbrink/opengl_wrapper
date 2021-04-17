#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h> // include glad to get all the required OpenGL headers

struct BufferElement {
	uint32_t type;
	uint32_t count;
	uint8_t normalized;
	uint32_t offset;
	static uint32_t getTypeSize(uint32_t type);
};



class BufferLayout{
public:
	BufferLayout();
	uint32_t getStride() const;
	std::vector<BufferElement> getElements() const;
	template <typename T> void push(uint32_t count, uint32_t offset);

private:
	std::vector<BufferElement> elements;
	uint32_t stride;
};

