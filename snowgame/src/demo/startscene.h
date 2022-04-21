#ifndef STARTSCENE_H
#define STARTSCENE_H
#include <common/scene.h>
class StartScene : public Scene
{
public:
    StartScene(/* args */);
    ~StartScene();
    virtual void update(float deltaTime);
};

#endif /* STARTSCENE_H */