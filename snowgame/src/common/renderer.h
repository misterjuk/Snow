/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * - OpenGL documentory is used
 */
#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/scene.h>
#include <common/camera.h>
#include <common/sprite.h>

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void renderScene(Scene* scene);
	void renderGameObject(GameObject* gameObject);
	
	GLFWwindow* window() { return _window; };

	float updateDeltaTime();

private:
	int init();

	GLFWwindow* _window;

	GLuint loadShaders(
		const std::string& vertex_file_path,
		const std::string& fragment_file_path
	);
	ResourceManager resman;

	GLuint _programID;

	Camera* _camera; // reference to scene->camera

};

#endif /* RENDERER_H */
