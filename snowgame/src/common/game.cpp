/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <common/game.h>

#include <common/input.h>
#include <iostream>

Game::Game()
{
     sceneID = 0;
     input = new Input();
}
Game::~Game()
{
    _scenes.clear();
}
void Game::update()
{
   for (size_t i = 0; i < _scenes.size(); i++)
   {
       _scenes[i]->setInput(input);
   }
   input->updateInput(renderer.window());
   //gives abillity to track input in the scenes
}
