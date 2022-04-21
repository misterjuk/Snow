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