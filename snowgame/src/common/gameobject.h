/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <common/sprite.h>
#include <glm/glm.hpp>
#include <vector>

class GameObject
{
public:
   GameObject(const std::string& spritepath);
   GameObject();
   virtual ~GameObject(); 

   glm::vec3 position;
   float rotation;
   glm::vec3 scale;
   Sprite* sprite;
protected:  
};

#endif /* GAMEOBJECT_H */