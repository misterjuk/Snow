#ifndef  SNOWFLAKE_H
#define  SNOWFLAKE_H

#include <glm/glm.hpp>
#include <common/scene.h>
#include <common/gameobject.h>


class Snowflake : public GameObject
{
public:
	Snowflake(const std::string& spritepath);
	virtual ~Snowflake();	
	glm::vec3 velocity;
private:
};
#endif /* SNOWFLAKE_H */
