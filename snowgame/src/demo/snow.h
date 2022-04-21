#ifndef SNOW_H
#define SNOW_H

#include <common/gameobject.h>
#include <vector>
class Snow : public GameObject
{
public:
 Snow(const std::string& spritepath);
     ~Snow();
};


#endif /* SNOW_H */