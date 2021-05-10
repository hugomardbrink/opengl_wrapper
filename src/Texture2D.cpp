#include "Texture2D.h"

/**
 * Creates a opengl compatible texture with a .png or .jpg
 * @param imagePath The systempath to image
 */
Texture2D::Texture2D(const std::string& imagePath)
{
	int32_t width, height, nrChannels;
	uint32_t colourFormat = 0;
	uint8_t* data;

	std::string format = imagePath.substr(imagePath.length() - 3, imagePath.length());
	
	// Matches file extension with correct opengl colour format
	if (format._Equal("jpg")) colourFormat = GL_RGB;
	else if (format._Equal("png")) colourFormat = GL_RGBA;
	else std::cout << "ERROR::TEXTURE2D::IMAGE_EXTENSION_NOT_SUPPORTED" << std::endl;

	// Flips texture due to mapping in opengl
	stbi_set_flip_vertically_on_load(1);
	// Loads image as uint8 array
	data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);


	// Declares how the texture behaves
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);


	glTexImage2D(GL_TEXTURE_2D, 0, colourFormat, width, height, 0, colourFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	// Deallocate memory
	stbi_image_free(data);
}

/**
 * Deallocates GPU-Resource
 */
Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_rendererID);
}

/**
 * Binds texture to specified sample slot
 * @param sampleSlot The sample slot used to bind to shader
 */
void Texture2D::bind(uint32_t sampleSlot)
{
	glActiveTexture(GL_TEXTURE0 + sampleSlot);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}
