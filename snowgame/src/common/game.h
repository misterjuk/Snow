#ifndef GAME_H
#define GAME_H

#include <common/renderer.h>
#include <common/input.h>
class Game
{
public:
    Game();
     virtual ~Game();
    virtual void update();
    virtual Scene* getScene() { return _scenes[sceneID];};
    std::vector<Scene*>& scenes() {return _scenes;};
     
protected:
    std::vector<Scene*> _scenes;
    Renderer renderer;
    int sceneID = 0;
    Input* input;
   
private:

};
#endif /* GAME_H */