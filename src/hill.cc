#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "globals.hh"
#include "hill.hh"

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
		render_segment( segments[0] );
		// for (size_t i = current_segment(); i < current_segment()+3; i++) {
		// 	render_segment( segments[i] );
		// }
	rlEnd();

	rlSetTexture(0);
}
