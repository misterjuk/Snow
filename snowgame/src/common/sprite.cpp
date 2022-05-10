/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#include <iostream>
#include <cstdio>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <common/sprite.h>

Sprite::Sprite(const std::string& imagepath)
{
	// Transform
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0.0f;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_texture = new Texture();
	_mesh = new Mesh();

	_filename = imagepath;
}

Sprite::~Sprite()
{
	delete _texture;
	delete _mesh;
}


