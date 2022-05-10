/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/mygame.h>
#include <demo/myscene.h>
#include <demo/startscene.h>
#include <demo/gameoverscene.h>


MyGame::MyGame()
{
    _scenes.push_back(new StartScene());
    _scenes.push_back(new MyScene());
    _scenes.push_back(new GameOverScene());
}
MyGame::~MyGame()
{
    _scenes.clear();

    //TODO make destructor
}
void MyGame::play()
{   
    do{
        //DEBUG FEATURE
        if(input->getKeyDown(KeyCode::Z))
        {
            sceneID--;
            if(sceneID <= 0)
            {
                sceneID = 0;
            }
        }
        if(input->getKeyDown(KeyCode::X))
        {
            sceneID++;
            if(sceneID >= _scenes.size())
            {
                sceneID = _scenes.size()-1;
            }
        }  
         
        float dt = renderer.updateDeltaTime();
        Scene* currentscene = getScene();
        switch (currentscene->state)
        {
            case State::GameOver:   
                currentscene->state = State::NotActive;
                sceneID = _scenes.size()-1;
                currentscene = _scenes.back();
                //hard coded
                
                break;
            case State::StartGame:
                currentscene->state = State::NotActive;
                sceneID = 1;
                currentscene = _scenes[sceneID];
                _scenes[sceneID]->state = State::Active;         
                //hard coded         
                break;
            case State::StartNewGame:
                currentscene->state = State::NotActive;
                sceneID = 1;
                currentscene = _scenes[sceneID];
                _scenes[sceneID]->state = State::Reset;
                _scenes[sceneID]->init();    
                //hard coded
                break;
            case State::Quit:
                currentscene->state = State::NotActive;
                sceneID = 0;
                currentscene = _scenes[0];
                //hard coded
                break;
            default:
                break;
        }
        currentscene->camera()->computeViewMatrixFromInput(renderer.window(), dt);
        renderer.renderScene(currentscene);
        Game::update();
        currentscene->update(dt);
        
    }while(glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(renderer.window()) == 0 );
    delete getScene();// TODO delete all scenes
    //  ~MyGame() // probably its better
}
  