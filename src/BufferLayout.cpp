#include "BufferLayout.h"



BufferLayout::BufferLayout() : 
stride(0) {}

template <typename T> void BufferLayout::push(uint32_t count, uint32_t offset) 
{
	std::cout << "ERROR::BUFFERLAYOUT::PUSHED_TYPE_NOT_SUPPORTED" << std::endl;
	static_assert(false);
}

template<> void BufferLayout::push<float>(uint32_t count, uint32_t offset) 
{
	elements.push_back({ GL_FLOAT, count, GL_FALSE, offset * sizeof(GL_FLOAT) });
	stride += count;
}

template<> void BufferLayout::push<uint32_t>(uint32_t count, uint32_t offset) 
{
	elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, offset * sizeof(GL_UNSIGNED_INT) });
	stride += count;
}

template<> void BufferLayout::push<uint8_t>(uint32_t count, uint32_t offset) 
{
	elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE, offset * sizeof(GL_UNSIGNED_BYTE) });
	stride += count;
}

uint32_t BufferLayout::getStride() const 
{
	return stride;
}

std::vector<BufferElement> BufferLayout::getElements() const
{
	return elements;
}

uint32_t BufferElement::getTypeSize(uint32_t type) 
{
	switch (type) 
	{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
	}
	return 0;
}