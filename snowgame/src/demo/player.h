/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <common/scene.h>
#include <common/input.h>
class Player : public GameObject
{
private:
    
public:
 Player(const std::string& spritepath);
 ~Player();
 virtual void update();
 float Speed = 250.0f;
 private:
    
};

#endif /* PLAYER_H */