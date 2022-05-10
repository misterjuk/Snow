/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#include <common/gameobject.h>

#include <glm/glm.hpp>

GameObject::GameObject(const std::string& spritepath 
/*const std::string& spritepath = nullptr ,
to not write the constructor second time */)
{
    sprite = new Sprite(spritepath);
    position = glm::vec3(0.0f,0.0f,0.0f);
    rotation = 0.0f;
    scale = glm::vec3(1.0f);
}
GameObject::GameObject() {
    sprite = nullptr;
    position = glm::vec3(0.0f,0.0f,0.0f);
    rotation = 0.0f;
}
GameObject::~GameObject()
{
    sprite = nullptr;
}