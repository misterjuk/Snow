#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <GL/glew.h>
#include <common/sprite.h>
class ResourceManager
{
public:
    ResourceManager(/* args */);
    virtual ~ResourceManager();

    // Texture* getTexture(const std::string& filename);
    void cleanup();

private:
    void deleteTexture(const std::string& filename);
    std::map<std::string, GLuint*> _textures;
};

#endif /* RESOURCEMANAGER_H */