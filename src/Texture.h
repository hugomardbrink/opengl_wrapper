#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>
#include <string>
#include "stb_image.h"
#include "Shader.h"

/**
 * A virtual class that forces a bind method and a opengl ID on its children
 */
class Texture
{
public:
	virtual void bind(uint32_t sampleSlot) = 0;
protected:
	uint32_t m_rendererID;
};

