/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
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
  virtual bool init();
  virtual ~MyScene();
  virtual void update(float deltaTime);

  Player* player;
  std::vector<Snowflake*> snowflakes;
  std::vector<Snow*> snow;
  std::vector<GameObject*> numbers;

  unsigned int Score = 0;

private:
  unsigned int snowlayercount = 0;
  unsigned int maxsnowlayer = 3; //snow layers to lose
  float timeToSpawnSnowflake = 2.0f; //time to spawn snowflake
	float timeLeftToSpawn;
  glm::vec3 snowflakeVelocity; //make it just a float?
  Collider* _collider;

  bool isInitialized = false;

  void clear();
  void resetGame();
  void updateScore(int score);
  void InstantiateSnowLayer();
  bool CheckCollisionWithSnow(GameObject* gameobject);
};


#endif MYSCENE_H