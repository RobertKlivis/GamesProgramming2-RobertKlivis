#include "ObjectTexture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

ObjectTexture::ObjectTexture()
{
}

void ObjectTexture::init(const std::string& fileName)
{
	int width, height, numComponents; //set integers for width, height and number of components
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //loads the image and stores the neccesary data

	if (imageData == NULL) //if no imageData is found
	{
		std::cerr << "texture failed to load" << fileName << std::endl; //display the error message
	}

	glGenTextures(1, &textureHandler); //set number and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //binds texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wraps texture outside the set width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wraps texture outside the set height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //uses linear filtering for minification
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //uses linear filtering for magnification

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //sets target, minimapping level, pixel format, width, height, border size, input format, data type of texture and image data

	stbi_image_free(imageData);
}

ObjectTexture::~ObjectTexture()
{
	glDeleteTextures(1, &textureHandler); //set number and address of textures
}

void ObjectTexture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //makes sure that one of 32 textures are being used

	glActiveTexture(GL_TEXTURE0 + unit); //sets active texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler); //sets type and texture that has to binded to the unit
}
