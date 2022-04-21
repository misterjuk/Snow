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
    
    //TODO somehow avoid passing renderer, maybe another way to get inputs
}