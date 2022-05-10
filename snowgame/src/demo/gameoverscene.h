/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <common/scene.h>
class GameOverScene : public Scene
{
public:
    GameOverScene(/* args */);
    ~GameOverScene();
    virtual void update(float deltaTime);
};


#endif /* GAMEOVERSCENE_H */