#include "Texture2D.h"

Texture2D::Texture2D(const std::string& imagePath)
{
	int32_t width, height, nrChannels;
	uint32_t colorFormat = 0;
	uint8_t* data;

	std::string format = imagePath.substr(imagePath.length() - 3, imagePath.length());
	
	if (format._Equal("jpg")) colorFormat = GL_RGB;
	else if (format._Equal("png")) colorFormat = GL_RGBA;
	else std::cout << "ERROR::TEXTURE2D::IMAGE_EXTENSION_NOT_SUPPORTED" << std::endl;


	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);


	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &rendererID);
}

void Texture2D::bind(uint32_t sampleSlot)
{
	glActiveTexture(GL_TEXTURE0 + sampleSlot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}
