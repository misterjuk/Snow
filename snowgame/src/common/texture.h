/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
class Texture
{
public:
    Texture(/* args */);
    virtual ~Texture();

    GLuint loadTGA(const std::string& imagepath);
    GLuint getGLTexture() { return _textureID; };

    unsigned int width() { return _width; };
	unsigned int height() { return _height; };
    

private:
	unsigned int _width;
	unsigned int _height;
    GLuint _textureID = 0;
};

#endif /* TEXTURE_H */