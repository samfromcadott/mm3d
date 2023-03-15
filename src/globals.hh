#pragma once

#include <raylib.h>

const Color sky_color = {106, 173, 253, 255};

const int screen_width_internal = 320;
const int screen_height_internal = 240;

const int screen_width = screen_width_internal * 3;
const int screen_height = screen_height_internal * 3;

extern Texture2D background;
extern Texture2D gravel;
extern Texture2D trees;
extern Texture2D grass;
