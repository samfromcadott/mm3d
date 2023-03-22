#pragma once

#include <vector>
#include <raylib.h>

class Player;
class Hill;
class Thing;

const Color sky_color = {106, 173, 253, 255};

const int screen_width_internal = 320;
const int screen_height_internal = 240;

const int screen_width = screen_width_internal * 3;
const int screen_height = screen_height_internal * 3;

const Vector3 up = {0.0, 0.0, 1.0};

extern Texture2D background;
extern Texture2D gravel;
extern Texture2D trees;
extern Texture2D grass;
extern Texture2D tree_sprite;
extern Texture2D rock_sprite;
extern Music theme;

extern Player player;
extern Hill hill;
extern Camera3D camera;
extern std::vector<Thing> things;
