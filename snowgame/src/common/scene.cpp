/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#include <iostream>
#include <common/scene.h>
#include <common/config.h>

#include <GL/glew.h>
#include <GL/GLU.h>
#include <GL/GL.h>

Scene::Scene()
{
	_camera = new Camera();
	_collider = new Collider();
	state = State::NotActive;
}

Scene::~Scene()
{
	// Delete all the sprites
	for (size_t i = 0; i < _gameobjects.size(); i++)
	{
		delete _gameobjects[i];
	}
	_gameobjects.clear();
	// Delete camera
	delete _camera;
}

void Scene::addGameObject(GameObject* gameobject)
{
	_gameobjects.push_back(gameobject);
}
void Scene::addGameObjectToTheFront(GameObject* gameobject)
{
	_gameobjects.insert(_gameobjects.begin(),gameobject);
}
void Scene::removeGameObject(GameObject* gameobject)
{
    auto i = find(_gameobjects.begin(), _gameobjects.end(), gameobject);
	_gameobjects.erase(i);
}
void Scene::clearAllGameObjects()
{
	 _gameobjects.clear();
}
void Scene::update(float deltaTime)
{	
	
	
}
bool Scene::CheckCollision(GameObject* gameobj1, GameObject* gameobj2)
{
	Rectangle rec1(
	gameobj1->position.x - gameobj1->sprite->width()/2, 
	gameobj1->position.y - gameobj1->sprite->height()/2,
	//giving offset to the collider because sprite renderered from the center and collider been rendered from edge
	gameobj1->sprite->width(),
	gameobj1->sprite->height()
	);
	Rectangle rec2(
	gameobj2->position.x - gameobj2->sprite->width()/2,
	gameobj2->position.y - gameobj2->sprite->height()/2,
	//giving offset to the collider because sprite renderered from the center and collider been rendered from edge
	gameobj2->sprite->width(),
	gameobj2->sprite->height()
	);
		if(_collider->rectangle2rectangle(rec1,rec2)) //check collsion between object and snow piece
		{
			return true;
		}
		else
		{
			return false;
		}
}
bool Scene::init()
{
	return true;
}

