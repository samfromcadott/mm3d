#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "thing.hh"
#include "globals.hh"
#include "player.hh"
#include "hill.hh"

Thing::Thing(Vector3 position, Vector3 velocity, float radius, float height) {
	this->position = position;
	this->velocity = velocity;
	this->radius = radius;
	this->height = height;
}

void Thing::render() {
	DrawCylinderWiresEx(
		position,
		Vector3Add(position, {0, 0, height}),
		radius, radius,
		8,
		MAGENTA
	);
}

void Thing::update() {
	position.z = hill.get_height(position.y);
	if ( collide() && !player.dead ) player.die();
}

bool Thing::collide() {
	float dist = Vector2Distance( {player.position.x, player.position.y}, {position.x, position.y} );
	if (dist < radius) return true;

	return false;
}
