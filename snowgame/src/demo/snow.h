/**
 * This file is part of the SNOW, intake assigment for Breda University of Applied Sciences
 *
 * - Copyright 2022 Yevhenii Ovramenko <misterjuk2005@gmail.com>
 * 
 */
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