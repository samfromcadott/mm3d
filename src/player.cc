#include <raylib.h>
#include <raymath.h>

#include "globals.hh"
#include "player.hh"
#include "hill.hh"

Player::Player() {
	player.position = {-2.0, 0.0, height};
}

void Player::update() {
	steer();
	position = Vector3Add(position, {0.0, 4.0f*GetFrameTime(), 0.0});
	position.z = hill.get_height(position.y) + height;
}

void Player::steer() {
	if ( IsKeyDown(KEY_LEFT) ) position.x -= steer_speed * GetFrameTime();
	if ( IsKeyDown(KEY_RIGHT) ) position.x += steer_speed * GetFrameTime();

	if (position.x < -4.0) position.x = -4.0;
	if (position.x > 0) position.x = 0;

}
