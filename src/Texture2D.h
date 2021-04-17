#pragma once
#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D(const std::string& imagePath, uint32_t colorFormat);
	~Texture2D();
	void bind(uint32_t sampleSlot);
};

