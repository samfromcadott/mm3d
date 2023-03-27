#include <vector>
#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

#include "globals.hh"
#include "player.hh"
#include "hill.hh"
#include "thing.hh"

float timer; // Time current run has lasted

Texture2D background;
Texture2D gravel;
Texture2D trees;
Texture2D grass;
Texture2D tree_sprite;
Texture2D rock_sprite;
Texture2D bigfoot_sprite;
Music theme;
Sound explosion_sound;

Player player;
Hill hill;
Camera3D camera;
std::vector<Thing> things;

void start_game();

int main() {
	// Initialization
	const float virtual_ratio = (float)screen_width/(float)screen_width_internal;

	InitWindow(screen_width, screen_height, "Mountain Mayhem 3D");
	InitAudioDevice();

	Camera2D worldSpaceCamera = { 0 };  // Game world camera
	worldSpaceCamera.zoom = 1.0f;

	// Camera setup
	camera = { 0 };
	camera.position = (Vector3){ -2.0, -8.0, 8.0 };
	camera.target = (Vector3){ -2.0, 0.0, 0.0 };
	camera.up = up;
	camera.fovy = 90.0;
	camera.projection = CAMERA_PERSPECTIVE;

	// Create the render texture
	RenderTexture2D render_target = LoadRenderTexture(screen_width_internal, screen_height_internal);

	Rectangle source_rect = { 0.0f, 0.0f, (float)render_target.texture.width, -(float)render_target.texture.height };
	Rectangle dest_rect = { -virtual_ratio, -virtual_ratio, screen_width + (virtual_ratio*2), screen_height + (virtual_ratio*2) };

	Vector2 origin = { 0.0f, 0.0f };

	SetTargetFPS(60);
	HideCursor();
	SetWindowIcon( LoadImage("assets/graphics/icon.png") );

	// Load the textures
	background = LoadTexture("assets/graphics/mountain.png");
	gravel = LoadTexture("assets/graphics/road.png");
	trees = LoadTexture("assets/graphics/trees.png");
	grass = LoadTexture("assets/graphics/grass.png");
	tree_sprite = LoadTexture("assets/graphics/tree_sprite.png");
	rock_sprite = LoadTexture("assets/graphics/rock_sprite.png");
	bigfoot_sprite = LoadTexture("assets/graphics/bigfoot_sprite.png");

	SetTextureWrap(gravel, TEXTURE_WRAP_MIRROR_REPEAT);
	SetTextureFilter(gravel, TEXTURE_FILTER_POINT);

	// Load audio
	theme = LoadMusicStream("assets/audio/theme.mp3");
	explosion_sound = LoadSound("assets/audio/explosion.wav");

	start_game();

	// Main game loop
	while ( !WindowShouldClose() ) {
		timer += GetFrameTime();

		// Update music
		UpdateMusicStream(theme);

		float volume = Lerp(0.0, 1.0, timer); // Fade in music at start
		volume = Clamp(volume, 0.0, 1.0);
		SetMusicVolume(theme, volume);

		// Update
		player.update();
		hill.update();
		for ( auto it = things.begin(); it != things.end(); ) {
			it->update();

			// Erase objects behind the player
			if ( it->position.y < player.position.y ) it = things.erase(it);
			else ++it;
		}

		if ( IsKeyPressed(KEY_R) && player.dead ) start_game();

		// Draw
		BeginTextureMode(render_target);
			// Draw the background
			ClearBackground(sky_color);
			int background_offset = Lerp(
				0,
				background.height,
				Vector3Normalize( Vector3Subtract(camera.target, camera.position) ).z
			);
			DrawTexture(background, 0, background_offset, WHITE);

			BeginMode3D(camera);
				hill.render();
				for ( auto it = things.rbegin(); it != things.rend(); ++it ) { // Things are rendered back to front
					it->render();
				}
			EndMode3D();
		EndTextureMode();

		BeginDrawing();
			DrawTexturePro(render_target.texture, source_rect, dest_rect, origin, 0.0f, WHITE);
		EndDrawing();
	}

	// Unloading
	UnloadRenderTexture(render_target); // Unload render texture
	UnloadTexture(background);
	UnloadTexture(gravel);
	UnloadTexture(grass);
	UnloadTexture(tree_sprite);
	UnloadTexture(rock_sprite);
	UnloadTexture(bigfoot_sprite);
	UnloadMusicStream(theme);
	UnloadSound(explosion_sound);

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

void start_game() {
	timer = 0.0;

	things.clear();
	player = Player();
	hill = Hill();

	StopMusicStream(theme);
	PlayMusicStream(theme);
}
