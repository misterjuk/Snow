/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/snowflake.h>
#include <common/config.h>

#include <glm/glm.hpp>

Snowflake::Snowflake(const std::string& spritepath)
{
	sprite = new Sprite(spritepath);
	scale = glm::vec3(1.0f);
	position = glm::vec3(rand() % WIDTH, 0.0f, 0.0f); //set random position from scene?
	velocity = glm::vec3 (0.0f, 100.0f, 0.0f);
	//velocity = glm::vec3(0.0f, rand() % 120, 0.0f);
}
Snowflake::~Snowflake()
{
	sprite = nullptr;
	//TODO make destructor
}

