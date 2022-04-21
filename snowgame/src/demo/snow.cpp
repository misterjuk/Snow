#include <demo/snow.h>
Snow::Snow(const std::string& spritepath)
{
    sprite = new Sprite(spritepath);
    scale = glm::vec3(1.0f);
}
Snow::~Snow()
{
    sprite = nullptr;
	delete this;
    //TODO make destructor
}