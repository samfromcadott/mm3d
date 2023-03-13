#include <math.h>       // Required for: sinf(), cosf()
#include <raylib.h>

const Color sky_color = {106, 173, 253, 255};

int main() {
	// Initialization
	const int screen_width_internal = 320;
	const int screen_height_internal = 240;

	const int screen_width = screen_width_internal * 3;
	const int screen_height = screen_height_internal * 3;

	const float virtual_ratio = (float)screen_width/(float)screen_width_internal;

	InitWindow(screen_width, screen_height, "Mountain Mayhem 3D");

	Camera2D worldSpaceCamera = { 0 };  // Game world camera
	worldSpaceCamera.zoom = 1.0f;

	Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
	screenSpaceCamera.zoom = 1.0f;

	// Define the camera to look into our 3d world
	Camera3D camera = { 0 };
	camera.position = (Vector3){ 10.0, 10.0, 10.0 };  // Camera position
	camera.target = (Vector3){ 0.0, 0.0, 0.0 };      // Camera looking at point
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
	Texture2D background = LoadTexture("assets/graphics/mountain.png");
	Texture2D gravel = LoadTexture("assets/graphics/road.png");

	// Main game loop
	while ( !WindowShouldClose() ) {
		// Draw
		BeginTextureMode(render_target);
			// Draw the background
			ClearBackground(sky_color);
			DrawTexture(background, 0, 0, WHITE);


			BeginMode3D(camera);
				DrawCube({0.0,0.0,0.0}, 2.0f, 2.0f, 2.0f, RED);
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
