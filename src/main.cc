#include <vector>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

#include "globals.hh"
#include "player.hh"
#include "hill.hh"
#include "thing.hh"

Texture2D background;
Texture2D gravel;
Texture2D trees;
Texture2D grass;

Player player;
Hill hill;
Camera3D camera;
std::vector<Thing> things;

void start_game();

int main() {
	// Initialization
	const float virtual_ratio = (float)screen_width/(float)screen_width_internal;

	InitWindow(screen_width, screen_height, "Mountain Mayhem 3D");

	Camera2D worldSpaceCamera = { 0 };  // Game world camera
	worldSpaceCamera.zoom = 1.0f;

	Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
	screenSpaceCamera.zoom = 1.0f;

	// Define the camera to look into our 3d world
	camera = { 0 };
	camera.position = (Vector3){ -2.0, -8.0, 8.0 };  // Camera position
	camera.target = (Vector3){ -2.0, 0.0, 0.0 };      // Camera looking at point
	// camera.position = (Vector3){ -2.0, 0.0, 1.5 };  // Camera position
	// camera.target = (Vector3){ -2.0, 1.0, 1.5 };     // Camera looking at point
	camera.up = (Vector3){ 0.0, 0.0, 1.0 };          // Camera up vector (rotation towards target)
	camera.fovy = 90.0;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	// Create the render texture
	RenderTexture2D render_target = LoadRenderTexture(screen_width_internal, screen_height_internal);

	// The target's height is flipped (in the source Rectangle), due to OpenGL reasons
	Rectangle sourceRec = { 0.0f, 0.0f, (float)render_target.texture.width, -(float)render_target.texture.height };
	Rectangle destRec = { -virtual_ratio, -virtual_ratio, screen_width + (virtual_ratio*2), screen_height + (virtual_ratio*2) };

	Vector2 origin = { 0.0f, 0.0f };

	SetTargetFPS(60);

	// Load the textures
	background = LoadTexture("assets/graphics/mountain.png");
	gravel = LoadTexture("assets/graphics/road.png");
	trees = LoadTexture("assets/graphics/trees.png");
	grass = LoadTexture("assets/graphics/grass.png");
	SetTextureWrap(gravel, TEXTURE_WRAP_MIRROR_REPEAT);
	SetTextureFilter(gravel, TEXTURE_FILTER_POINT);

	start_game();

	// Main game loop
	while ( !WindowShouldClose() ) {
		// Update
		player.update();
		hill.update();
		for (Thing& thing : things) {
			thing.update();
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
				// DrawCube({0.0,30.0,-1.0}, 2.0f, 2.0f, 2.0f, RED);
				hill.render();
				for (Thing& thing : things) {
					thing.render();
				}
			EndMode3D();
		EndTextureMode();

		BeginDrawing();
			DrawTexturePro(render_target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
		EndDrawing();
	}

	// Unloading
	UnloadRenderTexture(render_target); // Unload render texture
	UnloadTexture(background);
	UnloadTexture(gravel);

	CloseWindow();

	return 0;
}

void start_game() {
	things.clear();
	player = Player();
	hill = Hill();
}
