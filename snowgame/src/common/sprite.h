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

	GLuint texture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	unsigned int width() { return _width; };
	unsigned int height() { return _height; };

	void setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight);
	int frame(int f);

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

private:
	GLuint loadTGA(const std::string& imagepath);

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	unsigned int _width;
	unsigned int _height;

	float _pivotx;
	float _pivoty;
	int _frame;
	float uvdimx = 1.0f;
	float uvdimy = 1.0f;

	float uvoffsetx;
	float uvoffsety;

};

#endif /* SPRITE_H */
