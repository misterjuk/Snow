/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 *
 */
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <GL/glew.h>
#include <common/texture.h>
#include <common/mesh.h>


class ResourceManager
{
public:
    ResourceManager(/* args */);
    virtual ~ResourceManager();

    Texture* getTexture(const std::string& filename);
    Mesh* getMesh(const std::string& filename, int width, int height);
    void cleanup();

private:
    void deleteTexture(const std::string& filename);
    void deleteMesh(const std::string& filename);
    std::map<std::string, Texture*> _textures;
    std::map<std::string, Mesh*> _meshes;
};

#endif /* RESOURCEMANAGER_H */