#include <demo/snowflake.h>
#include <common/config.h>

#include <glm/glm.hpp>

Snowflake::Snowflake(const std::string& spritepath)
{
	sprite = new Sprite(spritepath);
	scale = glm::vec3(4.0f,4.0f,4.0f);
	position = glm::vec3(rand() % WIDTH, 0.0f, 0.0f); //set random position from scene?
	velocity = glm::vec3 (0.0f, 100.0f, 0.0f);
	//velocity = glm::vec3(0.0f, rand() % 120, 0.0f);
}
Snowflake::~Snowflake()
{
	sprite = nullptr;
	//TODO make destructor
}

