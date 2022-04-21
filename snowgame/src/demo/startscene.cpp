#include <demo/startscene.h>

#include <iostream>
StartScene::StartScene()
{
    GameObject* StartSprite = new GameObject("assets/snowflake.tga");
    StartSprite->position = glm::vec3(WIDTH/2, HEIGHT/2, 0.0f);
    StartSprite->scale = glm::vec3(5.0f);
    addGameObject(StartSprite);
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
    }
   
}
