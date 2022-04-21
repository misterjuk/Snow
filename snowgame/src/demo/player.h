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
};

#endif /* PLAYER_H */