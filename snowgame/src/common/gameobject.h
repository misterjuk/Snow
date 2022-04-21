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
   // glm::vec3 position() {return _position;};
   // glm::vec3 scale() {return _scale;};
   // float rotation() {return _rotation;};
   // Sprite* sprite() {return _sprite;};
   //std::vector<Sprite*> _spritebatch;
   glm::vec3 position;
   float rotation;
   glm::vec3 scale;
   Sprite* sprite;
protected:
   
   
};

#endif /* GAMEOBJECT_H */