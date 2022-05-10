/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <demo/myscene.h>
#include <common/config.h>

#include <iostream>

MyScene::MyScene()
{
	clear();

	{//temporary problem fix, TODO fix that
	player = new Player("assets/player.tga");
	addGameObject(player);
	Snow* snowobj = new Snow("assets/snow.tga");
	snowobj->position = glm::vec3(0, HEIGHT, 0);
	addGameObject(snowobj);
	snow.push_back(snowobj);
	} 

    isInitialized = init();

}
MyScene::~MyScene()
{
	for(int i = 0; i < snowflakes.size(); i++)
	{
		removeGameObject(snowflakes[i]); //deleting each snowflake
	}
	for(int i = 0; i < snow.size(); i++)
	{
		removeGameObject(snow[i]); //deleting each snow piece
	}
	for(int i = 0; i < numbers.size(); i++)
	{
		removeGameObject(numbers[i]); //deleting each number piece
	}
	snow.clear();
	snowflakes.clear();
	numbers.clear();

	removeGameObject(player);	//deleting player
}
void MyScene::update(float deltaTime)
{
	if(isInitialized == true)
	{
    timeLeftToSpawn -= deltaTime;
	
	if(timeLeftToSpawn <= 0)
	{
		Snowflake* snowflake = new Snowflake("assets/snowflake.tga");
        addGameObject(snowflake);
        snowflakes.push_back(snowflake);
		timeLeftToSpawn = timeToSpawnSnowflake;
		//creating snowlfake	
	}	
   	for(size_t i = 0; i < snowflakes.size(); i++)
    	{ 
        snowflakes[i]->position += snowflakes[i]->velocity*deltaTime;
		snowflakes[i]->rotation += deltaTime;
		//move snowflakes with time
			if(CheckCollision(snowflakes[i], player))
			{ //checking collision of snowflake and player
				 Score += 10; 		
				 updateScore(Score);
				 //adding score for collecting snowflake
				 std::cout << Score;
				 removeGameObject(snowflakes[i]);	
				 //deleting the snowflake
				 snowflakes[i]->sprite = nullptr;
				 auto index = find(snowflakes.begin(), snowflakes.end() , snowflakes[i]);
				 snowflakes.erase(index);	
				//delete snowflake from the local vector (snowlflakes)
				break;			 				
			}
			if(CheckCollisionWithSnow(snowflakes[i])) //check snowflake collision with snow
			// maybe its good idea to check collision only for the first snoflake,
			// because it is the closest to the snow
			 {
				for(int j = 0; j < snowflakes.size();j++)
			     {
					 removeGameObject(snowflakes[j]);
					//clear all snowflakes
			     }			
				  snowflakes.clear();			
			      InstantiateSnowLayer(); //creating new snow layer	   
				  player->position.y = snow.back()->position.y - snow[0]->sprite->height();
				  //set player position on the top of the snow
			}
		
    	}

	//player movement
	if(input->getKey(KeyCode::A))
    {
        player->position -= glm::vec3(player->Speed, 0.0f , 0.0f)*deltaTime;
    }
     if(input->getKey(KeyCode::D))
    {
        player->position += glm::vec3(player->Speed, 0.0f , 0.0f)*deltaTime;
    }
	player->update();

	if(input->getKeyDown(KeyCode::Backspace))
    {
        state = State::Quit; //quit to start scene
    }
	if(input->getKeyDown(KeyCode::R))
    {
       resetGame(); //reset the game
    }
	}
	else
	{
		isInitialized = init();
	}
}
void MyScene::InstantiateSnowLayer()
{
	//spawning new snow layer when collision happens
	if(snowlayercount <= maxsnowlayer) 
	{
		if(snow.size() != 0)
		{
			if(snow[0]->sprite->height() != 0)
		 	{
				int n = ceil(WIDTH / snow[0]->sprite->width());
				for(int i = 0 ; i <= n+1; i++)
				{
				Snow* snowobj = new Snow("assets/snow.tga");
			
				snow.push_back(snowobj);
				
				snowobj->position = glm::vec3
				(
				i*snow[0]->sprite->width(),
				HEIGHT-snow[0]->sprite->height()*snowlayercount,
				0.0f
			 	);
				addGameObject(snowobj);
				} 
			}
		}

		snowlayercount++;
	}
	else
	{
		state = State::GameOver;
	}
}
bool MyScene::CheckCollisionWithSnow(GameObject* gameobject)
{
	Rectangle rec1(gameobject->position.x - gameobject->sprite->width()/2, gameobject->position.y - gameobject->sprite->height()/2, gameobject->sprite->width(), gameobject->sprite->height());
	//creating rectangle collider for the gameobject that was passed in agruments
	for(int i = 0 ; i < snow.size();i++)
	{	
		Rectangle rec2(
			snow[i]->position.x - snow[i]->sprite->width()/2,
		 	snow[i]->position.y - snow[i]->sprite->height()/2,
			snow[i]->sprite->width(),
		  	snow[i]->sprite->height()
			  );
			  //creating rectangle collider for each snow piece
			if(_collider->rectangle2rectangle(rec1,rec2)) //check collsion between object and snow piece
			{
				return true;
			}
	}
	return false;
}
bool MyScene::init()
{
	if(state == State::Reset)
	{
		resetGame(); //reset the game
	}
	state = State::Active;
	if(player->sprite->height() != 0) //before rendering the height = 0, TODO fix that
	{
    _collider = new Collider();
	snowlayercount = 0;
    InstantiateSnowLayer();
	updateScore(Score);
	if( snow.size() != 0)	//before rendering the height = 0, TODO fix that
	{
		player->position.y = snow[0]->position.y - player->sprite->height(); 
		//place player on the top of the snow
		GameObject* house = new GameObject("assets/houseflipped.tga");
		house->position = glm::vec3(320.0f,HEIGHT-200.0f,0.0f);
		addGameObjectToTheFront(house);
		//spawning the house
	} 
    timeLeftToSpawn = timeToSpawnSnowflake;	
	return true;
	}
	return false;
}
void MyScene::clear()
{
	snowflakes.clear();
	snow.clear();
	numbers.clear();
	clearAllGameObjects();	
	//clear all vectors
}
void MyScene::resetGame()
{
	clear();

		{//temporary problem fix, TODO fix that
		player = new Player("assets/player.tga");
		addGameObject(player);
		Snow* snowobj = new Snow("assets/snow.tga");
		snowobj->position = glm::vec3(0, HEIGHT, 0);
		addGameObject(snowobj);
		snow.push_back(snowobj);
		} 
		
	isInitialized = false;
	Score = 0;
}
void MyScene::updateScore(int score)
{
	GameObject* number;
	if(numbers.size() !=0)
	{
		for (size_t i = 0; i < numbers.size(); i++)
		{
			removeGameObject(numbers[i]);
		}	
	}
	numbers.clear(); 
	//clear all previous numbers

	std::string std = std::to_string(score);
	for (size_t i = 0; i < std.size(); i++)
	{
		switch (std[i])
		{
		case '0':
			number = new GameObject("assets/number_zero.tga");
			break;
		case '1':
			number = new GameObject("assets/number_one.tga");
			break;
		case '2':
			number = new GameObject("assets/number_twoflipped.tga");
			break;
		case '3':
			 number = new GameObject("assets/number_three.tga");
			break;
		case '4':
			number = new GameObject("assets/number_fourflipped.tga");
			break;
		case '5':
			number = new GameObject("assets/number_fiveflipped.tga");
			break;
		case '6':
			number = new GameObject("assets/number_sixflipped.tga");
			break;
		case '7':
			number = new GameObject("assets/number_sevenflipped.tga");
			break;
		case '8':
			number = new GameObject("assets/number_eight.tga");
			break;	
		case '9':
			number = new GameObject("assets/number_nineflipped.tga");
			break;					
		default:
			break;
		}
		number->position = glm::vec3(WIDTH/2 + i*60.0f,60.0f, 0.0f);
		number->scale = glm::vec3(1.0f);
		addGameObject(number);		
		numbers.push_back(number);
		//spawn a number
	}
	
}