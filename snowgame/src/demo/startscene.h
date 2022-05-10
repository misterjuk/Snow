/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#ifndef STARTSCENE_H
#define STARTSCENE_H
#include <common/scene.h>
class StartScene : public Scene
{
public:
    StartScene(/* args */);
    ~StartScene();
    virtual void update(float deltaTime);
};

#endif /* STARTSCENE_H */