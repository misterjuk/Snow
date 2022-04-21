#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <common/gameobject.h>
class Text : public GameObject
{
public:
    Text(const std::string& spritepath);
    virtual ~Text();
    virtual void update();
    void clearMessage();
    void message(std::string message);

    std::string message() {return _message;};
private: 
    std::string _message;
    std::vector<Sprite*> _spritebatch;
};

#endif /* TEXT_H */