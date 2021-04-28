#pragma once
#include "Texture.h"
#include <stdexcept>


/*
*  A 2D texture for binding to a shader sample, supports .png and .jpg
*/
class Texture2D : public Texture
{
public:
	Texture2D(const std::string& imagePath);
	~Texture2D();
	void bind(uint32_t sampleSlot);
};

