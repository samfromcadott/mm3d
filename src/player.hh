#pragma once

#include <raylib.h>

class Player {
private:
	float steer_speed = 3.0;

	void steer();

public:
	Vector3 position;

	void update();
};
