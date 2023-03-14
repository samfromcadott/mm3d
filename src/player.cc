#include <raylib.h>

#include "player.hh"

void Player::update() {
	steer();
}

void Player::steer() {
	if ( IsKeyDown(KEY_LEFT) ) position.x -= steer_speed * GetFrameTime();
	if ( IsKeyDown(KEY_RIGHT) ) position.x += steer_speed * GetFrameTime();

	if (position.x < -4.0) position.x = -4.0;
	if (position.x > 0) position.x = 0;

}
