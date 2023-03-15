#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "globals.hh"
#include "hill.hh"
#include "player.hh"

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
	rlVertex3f(-road_width-grass_width, s.start.y, s.end.z+tree_height);
	rlTexCoord2f(0.0, 1.0);
	rlVertex3f(-road_width-grass_width, s.start.y, s.start.z);

	rlTexCoord2f(0.0, 1.0);
	rlVertex3f(grass_width, s.start.y, s.start.z);
	rlTexCoord2f(0.0, 0.0);
	rlVertex3f(grass_width, s.start.y, s.end.z+tree_height);
	rlTexCoord2f(2.0, 0.0);
	rlVertex3f(grass_width, s.end.y, s.end.z+tree_height);
	rlTexCoord2f(2.0, 1.0);
	rlVertex3f(grass_width, s.end.y, s.end.z);
}

void Hill::render() {
	rlBegin(RL_QUADS);
		rlColor4f(1.0, 1.0, 1.0, 1.0);
		for (size_t i = current_segment(); i < current_segment()+4; i++) {
			Segment& s = segments[i];
			render_segment( s );
		}
	rlEnd();

	rlSetTexture(0);
}

void Hill::update() {
	// Check if the player if close to the end
	if ( current_segment() >= segments.size() - 3 )
		add_segment();
}


float Hill::get_height(float y) {
	return 0;
}

int Hill::current_segment() {
	return int(player.position.y / segment_length);
}

void Hill::add_segment() {
	Segment new_segment;
	new_segment.start = segments.back().end;
	new_segment.end = Vector3Add(new_segment.start, {0.0, segment_length, 0.0});
	segments.push_back(new_segment);
}
