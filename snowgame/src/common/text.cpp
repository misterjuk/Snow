#include <common/text.h>

Text::Text(const std::string& spritepath)
{
    _message = "";
	sprite = new Sprite(spritepath);
}
Text::~Text()
{
    clearMessage();
}
void Text::update()
{

}
void Text::message(std::string message)
{
    clearMessage();
	_message = message;

	unsigned int s = _message.size();
	for (unsigned int i = 0; i < s; i++) {
		Sprite* character = new Sprite("fonts/font.tga");
		float uvwidth = 1.0f / 16;
		float uvheight = 1.0f / 8;
		character->setupSprite("fonts/font.tga", 0.5f, 0.5f, uvwidth, uvheight);
		char c = _message[i];
		character->position.x = i*32; // half spacing between 64px wide characters
		int index = (int) c-32;
		if (index<0) { index = 0; }
		character->frame(index);

		_spritebatch.push_back(character);
	}
}
void Text::clearMessage()
{
	for (int i=0; i<_spritebatch.size(); i++) {
		delete _spritebatch[i];
	}	
    _spritebatch.clear();

	_message = "";
}