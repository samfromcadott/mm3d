#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "globals.hh"
#include "player.hh"
#include "hill.hh"

Player::Player() {
	position = {-hill.road_width/2.0f, 0.0, height};
	speed = 4.0;
	dead = false;
}

void Player::update() {
	steer();

	// Determine velocity
	float slope = hill.get_slope( hill.current_segment() );
	float friction = 5.0 * GetFrameTime();
	float acceleration = 9.0 * GetFrameTime();

	if (dead) {
		dead_update();
	} else {
		speed += (slope * acceleration) - friction;
		speed = Clamp(speed, min_speed, max_speed);
	}

	const Segment& s = hill.segments[ hill.current_segment() ];
	Vector3 direction = Vector3Subtract(s.end, s.start);
	direction = Vector3Normalize(direction);

	Vector3 velocity = Vector3Scale(direction, speed*GetFrameTime());

	// Update position
	// position = Vector3Add(position, {0.0, speed*GetFrameTime(), 0.0});
	position = Vector3Add(position, velocity);
	position.z = hill.get_height(position.y) + height;

	// Update camera
	camera.position = position;
	float target_height = hill.get_height(position.y + 1.0) + height;
	Vector3 target = {position.x, position.y+1.0f, target_height};
	camera.target = target;
}

void Player::steer() {
	if (dead) return;
	if ( IsKeyDown(KEY_LEFT) ) position.x -= steer_speed * GetFrameTime();
	if ( IsKeyDown(KEY_RIGHT) ) position.x += steer_speed * GetFrameTime();

	if (position.x < -hill.road_width) position.x = -hill.road_width;
	if (position.x > 0) position.x = 0;
}

void Player::dead_update() {
	if (!dead) return;
	if (height > 0.1)
		height -= 0.02;

	if (speed > 0)
		speed -= 0.02;

	if (speed < 0)
		speed = 0;
}
