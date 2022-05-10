/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
#include <common/resourcemanager.h>

#include <iostream>

ResourceManager::ResourceManager()
{
	std::cout << "#######################" << std::endl;
	std::cout << "resourcemanager created" << std::endl;
}

ResourceManager::~ResourceManager()
{
	std::cout << "################ ResourceManager::delete ################" << std::endl;
	// cleanup Textures
	this->cleanup();

	std::cout << "resourcemanager empty" << std::endl;
	std::cout << "#####################" << std::endl;

	std::cout << "resourcemanager closed" << std::endl;
}

void ResourceManager::cleanup()
{
	std::cout << "################ ResourceManager::cleanup ################" << std::endl;
	// textures
	std::cout << "---------- Delete Textures ----------" << std::endl;
	std::map<std::string, Texture*>::iterator text_it;
	for (text_it=_textures.begin(); text_it!=_textures.end(); ++text_it) {
		if (text_it->second != NULL) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			deleteTexture(text_it->first);
		}
	}
	_textures.clear();
}

// Texture
Texture* ResourceManager::getTexture(const std::string& filename)
{
	if (_textures[filename] != nullptr) {
		//std::cout << "return existing resource: " << filename << " (texture)" << std::endl;
		return _textures[filename];
	} else {
		
		Texture* t = new Texture();
		t->loadTGA(filename);
		_textures[filename] = t;
		std::cout << "return new resource: " << filename << " (texture)" << std::endl;
		return t;
	}

	//return nullptr;
}
Mesh* ResourceManager::getMesh(const std::string& filename ,int width, int height)
{

	if (_meshes[filename] != nullptr) {
		//std::cout << "return existing resource: " << filename << " (mesh)" << std::endl;
		return _meshes[filename];
	} else {
		Mesh* m = new Mesh();
		m->generateMesh(width, height);
		_meshes[filename] = m;

		std::cout << "return new resource: " << filename << " (mesh)" << std::endl;
		return m;
	}

	//return nullptr;
}

void ResourceManager::deleteTexture(const std::string& filename)
{
	//delete _textures[filename];
	_textures[filename] = NULL;

	std::cout << "==> deleting resource: " << filename << " (texture)" << std::endl;
}
void ResourceManager::deleteMesh(const std::string& filename)
{
	//delete _textures[filename];
	_meshes[filename] = NULL;

	std::cout << "==> deleting resource: " << filename << " (mesh)" << std::endl;
}

