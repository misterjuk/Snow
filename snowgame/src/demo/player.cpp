/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/player.h>
#include <common/scene.h>
#include <common/sprite.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

Player::Player(const std::string& spritepath)
{
    sprite = new Sprite(spritepath);
    scale = glm::vec3(1.0f);
}
Player::~Player()
{
    //TODO make destructor
}
void Player::update()
{
    
}