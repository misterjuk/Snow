#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <common/scene.h>
class GameOverScene : public Scene
{
public:
    GameOverScene(/* args */);
    ~GameOverScene();
    virtual void update(float deltaTime);
};


#endif /* GAMEOVERSCENE_H */