/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * - OpenGL documentory is used
 */
#include <common/texture.h>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
Texture::Texture()
{
	_width = 0;
	_height = 0;
	_textureID = 0;	
}
Texture::~Texture()
{
	glDeleteTextures(1, &_textureID);
}
GLuint Texture::loadTGA(const std::string& imagepath)
{
	std::cout << "Loading TGA: " << imagepath << std::endl;

	// Open the file on disk
	FILE *file;

	file = fopen(imagepath.c_str(), "rb");

	if (!file) {
		std::cout << "error: unable to open file" << std::endl;
		return 0;
	}

	// Read header (width, height, type, bitdepth)
	unsigned char type[4];
	unsigned char info[6];
	if (!fread (&type, sizeof (char), 3, file)) return 0;
	fseek (file, 12, SEEK_SET);
	if (!fread (&info, sizeof (char), 6, file)) return 0;

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		std::cout << "error: image type neither color or grayscale" << std::endl;
		fclose(file);
		return 0;
	}

	// Set width, height, bitdepth
	_width = info[0] + info[1] * 256;
	std::cout << "texture width:" << _width << std::endl;
	_height = info[2] + info[3] * 256;
	unsigned char bitdepth = info[4] / 8;

	if (bitdepth != 1 && bitdepth != 3 && bitdepth != 4) {
		std::cout << "bitdepth not 1, 3 or 4" << std::endl;
		fclose(file);
		return 0;
	}

	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_width & (_width - 1)) != 0) {
		std::cout << "warning: " << imagepath << "'s width is not a power of 2" << std::endl;
	}
	if ((_height & (_height - 1)) != 0) {
		std::cout << "warning: " << imagepath << "'s height is not a power of 2" << std::endl;
	}
	if (_width != _height) {
		std::cout << "warning: " << imagepath << " is not square" << std::endl;
	}

	// Calculate pixelbuffer size in bytes
	unsigned int imagesize = _width * _height * bitdepth;

	// Create a buffer
	unsigned char* data = new unsigned char [imagesize];

	// Read the actual data from the file into the buffer
	if (!fread(data, 1, imagesize, file)) return 0;

	// Everything is in memory now, close the file
	fclose(file);

	// Create one OpenGL texture
	// Be sure to also delete it from where you called this with glDeleteTextures()
	//GLuint textureID;
	glGenTextures(1, &_textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _textureID);

	// filter the Texture
	unsigned char filter = 1;
	switch (filter) {
		case 0:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case 1:
			// Linear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case 2:
			// Bilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case 3:
			// Trilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		default:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
	}

	// wrapping
	// GL_REPEAT, GL_MIRRORED_REPEAT or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// handle transparency and grayscale and give the image to OpenGL
	switch (bitdepth) {
		case 4:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
			break;
		case 1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, _width, _height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
			break;
		default:
			std::cout << "error: bitdepth not 4, 3, or 1" << std::endl;
			break;
	}

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Return the ID of the texture we just created
	return _textureID;
}