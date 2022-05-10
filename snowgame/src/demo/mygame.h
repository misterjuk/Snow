/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#ifndef MYGAME_H
#define MYGAME_H

#include <iostream>
#include <common/game.h>
#include <list>
#include <common/scene.h>
class MyGame : public Game
{
public:
    MyGame();
    virtual ~MyGame();
    virtual void play();
};

#endif /* MYGAME_H */