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
//    input->updateInput(renderer.window());

   for (size_t i = 0; i < _scenes.size(); i++)
   {
       _scenes[i]->setInput(input);
   }
   input->updateInput(renderer.window());
    //TODO switch between scenes
}
