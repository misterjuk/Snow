#include <demo/gameoverscene.h>

GameOverScene::GameOverScene()
{

}
GameOverScene::~GameOverScene()
{
    
}
void GameOverScene::update(float deltaTime)
{
    if(input->getKeyDown(KeyCode::R))
    {
        state = State::StartGame;
    }
    if(input->getKeyDown(KeyCode::Backspace))
    {
        state = State::Quit;
    }
}