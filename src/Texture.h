#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <stdint.h>
#include <string>
#include "lib/stb_image.h"
#include "Shader.h"

class Texture
{
public:
	virtual void bind(uint32_t sampleSlot) = 0;
protected:
	uint32_t rendererID;
};

