#pragma once

#include <raylib.h>

class Player {
private:
	float steer_speed = 3.5;
	float height = 1.5;
	float min_speed = 3.5;
	float max_speed = 30.0;

	void steer();

public:
	Vector3 position;
	float speed;

	void update();

	Player();
};
