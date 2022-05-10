/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/startscene.h>

#include <iostream>
StartScene::StartScene()
{
    GameObject* title = new GameObject("assets/titleflipped.tga");
    title->position = glm::vec3(WIDTH/2, HEIGHT-540, 0.0f);
    addGameObject(title);
    //spawning title
    GameObject* StartText = new GameObject("assets/pressEnterflipped.tga");
    StartText->position = glm::vec3(WIDTH/2, HEIGHT-320, 0.0f);
    addGameObject(StartText);
    //spawning description
    GameObject* description = new GameObject("assets/description.tga");
    description->position = glm::vec3(WIDTH/2, HEIGHT-120, 0.0f);
    addGameObject(description);
    //spawning description
   
}
StartScene::~StartScene()
{
    
}
void StartScene::update(float deltaTime)
{
    if(input->getKeyDown(KeyCode::Enter))
    {
        state = State::StartGame;
        std::cout << "button pressed";
        //start the game
    }
   
}
