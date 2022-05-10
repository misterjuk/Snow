/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <common/camera.h>
#include <common/sprite.h>
#include <common/collider.h>
#include <common/gameobject.h>
#include <common/input.h>

#include <iostream>

enum class State
{
	Quit, //quit from game to start scene
	// quit from gameoverscene to start scene
	GameOver,
	// game finished, neeed to load gameoverscene
	StartGame,
	StartNewGame,
	Active,
	NotActive,
	Reset
};
class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void update(float deltaTime);

	virtual bool init();

	void addGameObject(GameObject* gameobject);

	//give abillity to render some obejcts first
	void addGameObjectToTheFront(GameObject* gameobject);

	void removeGameObject(GameObject* gameobject);
	void clearAllGameObjects();

	Camera* camera() { return _camera; };

	std::vector<GameObject*>& gameobjects() {return _gameobjects;}
	void setInput(Input* inp)
	{
		this->input = inp;
	}
	bool CheckCollision(GameObject* gameobj1, GameObject* gameobj2);

	State state;

protected:
	Input* input;
private:
	std::vector<GameObject*> _gameobjects;
	Camera* _camera;
	Collider* _collider;
};

#endif /* SCENE_H */
