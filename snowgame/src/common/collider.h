#ifndef COLLIDER_H
#define COLLIDER_H

#include <GLFW/glfw3.h>
struct Rectangle
{
    float x;
	float y;
	float width;
	float height;
	Rectangle(float x_, float y_, float w, float h) {
		this->x = x_;
		this->y = y_;
		this->width = w;
		this->height = h;
	}
};

class Collider
{
	public:
	static bool rectangle2rectangle(const Rectangle& rect1, const Rectangle& rect2) {
		return (rect1.x < rect2.x + rect2.width &&
		    rect1.x + rect1.width > rect2.x &&
		    rect1.y < rect2.y + rect2.height &&
		    rect1.y + rect1.height > rect2.y);
	}
	private:
	
};



#endif /* COLLIDER_H */