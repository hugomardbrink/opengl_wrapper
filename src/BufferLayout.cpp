#include "BufferLayout.h"


/**
 * Creates empty object
 */
BufferLayout::BufferLayout() : 
m_stride(0) {}

/**
 * Catch all types not supported and throws error, should never be used
 * @param count The count of stored data, i.e a 3D position => count = 3
 */
template <typename T> void BufferLayout::push(uint32_t count) 
{
	std::cout << "ERROR::BUFFERLAYOUT::PUSHED_TYPE_NOT_SUPPORTED" << std::endl;
	static_assert(false);
}

/**
 * Pushes a stride sequence with values of type float
 * @param count The count of stored data, i.e a 3D position => count = 3
 */
template<> void BufferLayout::push<float>(uint32_t count) 
{
	m_elements.push_back({ GL_FLOAT, count, GL_FALSE, m_stride * sizeof(GL_FLOAT) });
	m_stride += count;
}

/**
 * Pushes a stride sequence with values of type uint32
 * @param count The count of stored data, i.e a 3D position => count = 3
 */
template<> void BufferLayout::push<uint32_t>(uint32_t count) 
{
	m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, m_stride * sizeof(GL_UNSIGNED_INT) });
	m_stride += count;
}

/**
 * Pushes a stride sequence with values of type uint8
 * @param count The count of stored data, i.e a 3D position => count = 3
 */
template<> void BufferLayout::push<uint8_t>(uint32_t count) 
{
	m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE, m_stride * sizeof(GL_UNSIGNED_BYTE) });
	m_stride += count;
}

/**
 * @return The stride count for the layout
 */
uint32_t BufferLayout::getStride() const 
{
	return m_stride;
}

/**
 * @return The stride sequences in a vector
 */
std::vector<BufferElement> BufferLayout::getElements() const
{
	return m_elements;
}