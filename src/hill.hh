#pragma once

#include <vector>

struct Segment {
	Vector3 start, end;
};

class Hill {
private:
	float tree_height = 6.0;
	float grass_width = 2.0;
	float segment_length = 8.0;
	int look_ahead = 4; // Number of segments to render

	void render_segment(Segment& s);
	void add_segment();

public:
	std::vector<Segment> segments;
	float road_width = 4.0;

	void render();
	void update();
	float get_height(float y); // Elevation at position y
	float get_slope(int i); // Slope of segment i
	int current_segment(); // Index of segment the player is on

	Hill();
};
