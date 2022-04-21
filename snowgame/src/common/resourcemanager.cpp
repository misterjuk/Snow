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
	std::map<std::string, GLuint*>::iterator text_it;
	for (text_it=_textures.begin(); text_it!=_textures.end(); ++text_it) {
		if (text_it->second != nullptr) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			deleteTexture(text_it->first);
		}
	}
	_textures.clear();
}

// Texture
// Texture* ResourceManager::getTexture(const std::string& filename)
// {
// 	if (_textures[filename] != nullptr) {
// 		//std::cout << "return existing resource: " << filename << " (texture)" << std::endl;
// 		return _textures[filename];
// 	} else {
		
// 		Texture* t;
// 		t->LoadTGAImage(filename, filter, wrap);
// 		_textures[filename] = t;
// 		std::cout << "return new resource: " << filename << " (texture)" << std::endl;
// 		return t;
// 	}

// 	return nullptr;
// }

void ResourceManager::deleteTexture(const std::string& filename)
{
	delete _textures[filename];
	_textures[filename] = nullptr;

	std::cout << "==> deleting resource: " << filename << " (texture)" << std::endl;
}
