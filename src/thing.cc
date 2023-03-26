#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "thing.hh"
#include "globals.hh"
#include "player.hh"
#include "hill.hh"

Thing::Thing(Texture2D* sprite, Vector3 position, Vector3 velocity, float radius, float height) {
	this->sprite = sprite;
	this->position = position;
	this->velocity = velocity;
	this->radius = radius;
	this->height = height;
}

void Thing::render() {
	Rectangle rect;

	// If the object is Bigfoot
	if (sprite == &bigfoot_sprite) {
		const float rate = 8; // Frame rate of animation
		const int length = 8; // Length (in frames) of the animation

		const float frame = int( GetTime() * rate ) % length; // Current frame

		rect = { frame * 64, 0, 64, 64 };
	} else {
		rect = { 0, 0, float(sprite->width), float(sprite->height) };
	}

	// DrawCylinderWiresEx(
	// 	position,
	// 	Vector3Add(position, {0, 0, height}),
	// 	radius, radius,
	// 	8,
	// 	MAGENTA
	// );

	DrawBillboardPro(
		camera,
		*sprite,
		rect,
		Vector3Add( position, {0,0,height} ),
		up,
		{radius*8, height*2},
		{0, 0},
		0.0,
		WHITE
	);
}

void Thing::update() {
	position = Vector3Add( position, Vector3Scale( velocity, GetFrameTime() ) );
	if ( collide() && !player.dead ) player.die();
}

bool Thing::collide() {
	float dist = Vector2Distance( {player.position.x, player.position.y}, {position.x, position.y} );
	if (dist < radius) return true;

	return false;
}
