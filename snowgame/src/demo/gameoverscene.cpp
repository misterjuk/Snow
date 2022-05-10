/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/gameoverscene.h>

GameOverScene::GameOverScene()
{
    GameObject* title = new GameObject("assets/gameover.tga");
    title->position = glm::vec3(WIDTH/2, HEIGHT-480, 0.0f);
    title->scale = glm::vec3(1.0f);
    addGameObject(title);
    //adding title sprite

    GameObject* StartSprite = new GameObject("assets/pressRflipped.tga");
    StartSprite->position = glm::vec3(WIDTH/2, HEIGHT-240, 0.0f);
    StartSprite->scale = glm::vec3(1.0f);
    addGameObject(StartSprite);
    //adding description sprite
}
GameOverScene::~GameOverScene()
{
    
}
void GameOverScene::update(float deltaTime)
{
    if(input->getKeyDown(KeyCode::R))
    {
        state = State::StartNewGame;
        //start new game
    }
    if(input->getKeyDown(KeyCode::Backspace))
    {
        state = State::StartNewGame;
        //start new game, because its already game over
    }
}