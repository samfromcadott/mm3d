#pragma once

#include <vector>

struct Segment {
	Vector3 start, end;
};

class Hill {
private:
	float road_width = 4.0;
	float tree_height = 6.0;
	float grass_width = 2.0;
	float segment_length = 8.0;

	void render_segment(Segment& s);

public:
	std::vector<Segment> segments;

	void render();
	float get_height(float y); // Elevation at position y
	int current_segment(); // Index of segment the player is on
};
