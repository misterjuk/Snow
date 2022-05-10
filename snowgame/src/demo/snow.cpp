/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/snow.h>
Snow::Snow(const std::string& spritepath)
{
    sprite = new Sprite(spritepath);
    scale = glm::vec3(1.0f);
}
Snow::~Snow()
{
    sprite = nullptr;
	delete this;
    //TODO make destructor
}