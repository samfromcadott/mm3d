#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "globals.hh"
#include "hill.hh"
#include "player.hh"
#include "thing.hh"

Hill::Hill() {
	segments = { {{0.0, 0.0, 0.0}, {0.0, segment_length, 0.0}} };
	for (int i = 0; i < look_ahead; i++) {
		add_segment();
	}
}

void Hill::render_segment(Segment& s) {
	// Road
	rlSetTexture(gravel.id);
	rlTexCoord2f(+1.0, 0.0);
	rlVertex3f(s.start.x, s.start.y, s.start.z);
	rlTexCoord2f(+1.0, segment_length);
	rlVertex3f(s.end.x, s.end.y, s.end.z);
	rlTexCoord2f(-1.0, segment_length);
	rlVertex3f(-road_width, s.end.y, s.end.z);
	rlTexCoord2f(-1.0, 0.0);
	rlVertex3f(-road_width, s.start.y, s.start.z);

	// Grass
	rlSetTexture(grass.id);
	rlTexCoord2f(+1.0, 0.0);
	rlVertex3f(-road_width, s.start.y, s.start.z);
	rlTexCoord2f(+1.0, segment_length);
	rlVertex3f(-road_width, s.end.y, s.end.z);
	rlTexCoord2f(0.0, segment_length);
	rlVertex3f(-road_width-grass_width, s.end.y, s.end.z);
	rlTexCoord2f(0.0, 0.0);
	rlVertex3f(-road_width-grass_width, s.start.y, s.start.z);

	rlTexCoord2f(+1.0, 0.0);
	rlVertex3f(grass_width, s.start.y, s.start.z);
	rlTexCoord2f(+1.0, segment_length);
	rlVertex3f(grass_width, s.end.y, s.end.z);
	rlTexCoord2f(0.0, segment_length);
	rlVertex3f(0.0, s.end.y, s.end.z);
	rlTexCoord2f(0.0, 0.0);
	rlVertex3f(s.start.x, s.start.y, s.start.z);

	// Trees
	rlSetTexture(trees.id);
	rlTexCoord2f(2.0, 1.0);
	rlVertex3f(-road_width-grass_width, s.end.y, s.end.z);
	rlTexCoord2f(2.0, 0.0);
	rlVertex3f(-road_width-grass_width, s.end.y, s.end.z+tree_height);
	rlTexCoord2f(0.0, 0.0);
	rlVertex3f(-road_width-grass_width, s.start.y, s.start.z+tree_height);
	rlTexCoord2f(0.0, 1.0);
	rlVertex3f(-road_width-grass_width, s.start.y, s.start.z);

	rlTexCoord2f(0.0, 1.0);
	rlVertex3f(grass_width, s.start.y, s.start.z);
	rlTexCoord2f(0.0, 0.0);
	rlVertex3f(grass_width, s.start.y, s.start.z+tree_height);
	rlTexCoord2f(2.0, 0.0);
	rlVertex3f(grass_width, s.end.y, s.end.z+tree_height);
	rlTexCoord2f(2.0, 1.0);
	rlVertex3f(grass_width, s.end.y, s.end.z);
}

void Hill::render() {
	rlPushMatrix();
	rlBegin(RL_QUADS);
		rlColor4f(1.0, 1.0, 1.0, 1.0);
		for (size_t i = current_segment(); i < current_segment()+look_ahead; i++) {
			Segment& s = segments[i];
			render_segment( s );
		}
	rlEnd();
	rlPopMatrix();

	rlSetTexture(0);
}

void Hill::update() {
	// Check if the player if close to the end
	if ( current_segment() >= segments.size() - (look_ahead-1) )
		add_segment();
}


float Hill::get_height(float y) {
	int index = int(y / segment_length);
	Segment& s = segments[index];
	float t = (y - index * segment_length) / segment_length; // Proportional distance to next segment

	// Lerp between the height of this segment and the next one
	float z = Lerp(s.start.z, s.end.z, t);
	return z;
}

float Hill::get_slope(int i) {
	Segment& s = segments[i];
	return (s.start.z - s.end.z) / segment_length;
}

int Hill::current_segment() {
	return int(player.position.y / segment_length);
}

void Hill::add_segment() {
	// Add the segment
	Segment new_segment;
	new_segment.start = segments.back().end;
	float drop = -GetRandomValue(0, segment_length);
	new_segment.end = Vector3Add(new_segment.start, {0.0, segment_length, drop});
	segments.push_back(new_segment);

	// Add things
	Thing new_thing = Thing(
		{ 0, new_segment.start.y+1.0f, 0 },
		{0,0,0},
		0.5,
		2.0
	);
	new_thing.position.z = get_height(new_thing.position.y);
	things.push_back(new_thing);
	// for (int i=0; i < int(segment_length); i++) {
	// 	Thing new_thing = Thing(
	// 		{ 0, new_segment.start.y+float(i), 0 },
	// 		{0,0,0},
	// 		0.5,
	// 		2.0
	// 	);
	// 	new_thing.position.z = get_height(new_thing.position.y);
	// 	things.push_back(new_thing);
	// }
}
