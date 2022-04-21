#ifndef MYSCENE_H
#define MYSCENE_H
#include <common/scene.h>
#include <demo/player.h>
#include <demo/snowflake.h>
#include <demo/snow.h>

class MyScene : public Scene
{
public:
     MyScene(/* args */);
  virtual void init();
   virtual ~MyScene();
   virtual void update(float deltaTime);
   void InstantiateSnowLayer();
   bool CheckCollisionWithSnow(GameObject* gameobject);

   void StartNewGame();

   Player* player;
   std::vector<Snowflake*> snowflakes;
   std::vector<Snow*> snow;

   unsigned int Score = 0;

   bool GameOver = false;
private:
  unsigned int snowlayercount = 0;
  unsigned int maxsnowlayer = 3; //snow layers to lose
  float timeToSpawnSnowflake = 2.0f; //time to spawn snowflake
	float timeLeftToSpawn;
  glm::vec3 snowflakeVelocity; //make it just a float?
  Collider* _collider;
};


#endif MYSCENE_H