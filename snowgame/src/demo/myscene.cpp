#include <demo/myscene.h>
#include <common/config.h>
#include <common/text.h>

#include <iostream>

MyScene::MyScene()
{
    init();
	//Text* text = new Text("fonts/font.tga");
	//text->message("hello world");
	//text->position = glm::vec3(WIDTH/2,HEIGHT/2, 0.0f);
	//std::cout << text->position.x;
	//text->scale = glm::vec3(.1f);
	//addGameObject(text);
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
	snow.clear();
	snowflakes.clear();

	removeGameObject(player);	//deleting player
}
void MyScene::update(float deltaTime)
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
				//adding score for collecting snowflake
				std::cout << Score;
				removeGameObject(snowflakes[i]);	
				snowflakes[i]->sprite = nullptr;
				auto index = find(snowflakes.begin(), snowflakes.end() , snowflakes[i]);
				snowflakes.erase(index);	
				//delete snowflake from the local vector (snowlflakes)
				break;			 	
				//deleting the snowflake
			}
			if(CheckCollisionWithSnow(snowflakes[i])) //check snowflake collision with snow
			// maybe its good idea to check collision only for the first snoflake,
			// because it is the closest to the snow
			 {
			    	std::cout << "collision called\n";	
				for(int j = 0; j < snowflakes.size();j++)
			     {
					removeGameObject(snowflakes[j]);
					snowflakes[j]->sprite = nullptr;
					//clear all snowflakes
			     }			
				 snowflakes.clear();			
			     InstantiateSnowLayer(); //creating new snow layer	   
				player->position.y = snow.back()->position.y - player->sprite->height()/2;  
			}
		
    	}

	if(input->getKey(KeyCode::A))
    {
        player->position -= glm::vec3(200.0f, 0.0f , 0.0f)*deltaTime;
    }
     if(input->getKey(KeyCode::D))
    {
        player->position += glm::vec3(200.0f, 0.0f , 0.0f)*deltaTime;
    }
	player->update(); // player needs renderer to move
	//TODO avoid passing renderer to player
	if(input->getKeyDown(KeyCode::Backspace))
    {
        state = State::Quit; //quit to start scene
    }
}
void MyScene::InstantiateSnowLayer()
{
	if(snowlayercount <= maxsnowlayer) 
	{
		Snow* snowobj = new Snow("assets/pencils.tga");
		int n = ceil(WIDTH / snowobj->sprite->width());
		for(int i = 0 ; i <= n; i++)
		{
			Snow* snowobj = new Snow("assets/pencils.tga");
			addGameObject(snowobj);
			snow.push_back(snowobj);
			
			snowobj->position = glm::vec3(
			i*snowobj->sprite->width(),
			HEIGHT-snowobj->sprite->height()*snowlayercount,
			0.0f
			  );
			  
		}
		snowlayercount++;
	}
	else
	{
		std::cout << "game has ended \n";
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
void MyScene::init()
{
	clearAllGameObjects();
	snowflakes.clear();
	snow.clear();
	//clear all
	player = new Player("assets/kingkong.tga");
    addGameObject(player);
    _collider = new Collider();
	snowlayercount = 0;
    InstantiateSnowLayer();
	player->position.y = snow.back()->position.y - player->sprite->height()/2;  
    timeLeftToSpawn = timeToSpawnSnowflake;
	state = State::Active;
}