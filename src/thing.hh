#pragma once

#include <raylib.h>

class Thing {
private:

public:
	Texture2D* sprite;
	Vector3 position, velocity;
	float radius, height;

	Thing(Texture2D* sprite, Vector3 position, Vector3 velocity, float radius, float height);
	Thing(){}
	virtual ~Thing(){}

	void render();
	void update();
	bool collide();

};
