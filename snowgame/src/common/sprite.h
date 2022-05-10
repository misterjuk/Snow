/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <common/resourcemanager.h>

class Sprite
{
public:
	Sprite(const std::string& imagepath);
	virtual ~Sprite();

	Texture* texture() { return _texture; };
	Mesh* mesh() { return _mesh;};
	void texture(Texture* texture) {_texture = texture;}
	void mesh(Mesh* mesh) {_mesh = mesh;}

	std::string filename() {return _filename;};

	unsigned int width() { return _texture->width(); };
	unsigned int height() { return _texture->height(); };
	//void width(int width) { _width = width; };
	//void height(int height) { _height = height; };

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

private:
	
	Texture* _texture;
	Mesh* _mesh;

	std::string _filename;

	//unsigned int _width;
	//unsigned int _height;

};

#endif /* SPRITE_H */
