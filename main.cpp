#include <iostream>
#include <array>
#include <raylib.h>
#include <string>

#include "particle.h"
#include "particle_grid.h"
#include "helper.h"
#include "brush.h"

void handleEvents();
void update();
void render();

constexpr int WIN_WIDTH{ 800 };
constexpr int WIN_HEIGHT{ 600 };
const std::string WIN_TITLE = "Sand Box Game";

PlayerState player_state{};
ParticleGrid game_grid{ WIN_WIDTH, WIN_HEIGHT };

auto brush_shape = std::make_shared<CircleBrush>();
Brush draw_brush(SAND, 10, brush_shape);
Brush erase_brush(AIR, 10, brush_shape);

int main() {
	SetTraceLogLevel(LOG_FATAL);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE.c_str());
	SetTargetFPS(240);

	// Game Loop
	while (!WindowShouldClose()) {
		handleEvents();
		update();
		render();
	}

	return EXIT_SUCCESS;
}

void handleEvents() {
	return;
}

void update() {
	// ---------- TITLE ---------- //
	std::string title_fps = WIN_TITLE + ", FPS: " + std::to_string(GetFPS());
	SetWindowTitle(title_fps.c_str());

	// ---------- PLAYER STATE ---------- //
	player_state.mouse_pos = GetMousePosition();
	player_state.is_mouseL_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	player_state.is_mouseR_down = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

	// ---------- SPAWN PARTICLE ---------- //
	if (player_state.is_mouseL_down && game_grid.isInBound(player_state.mouse_pos)) {
		game_grid.drawParticles(draw_brush, player_state.mouse_pos);
	}
	else if (player_state.is_mouseR_down && game_grid.isInBound(player_state.mouse_pos)) {
		game_grid.drawParticles(erase_brush, player_state.mouse_pos);
	}

	game_grid.updateAllParticles();
}

void render() {
	BeginDrawing();
	ClearBackground(BLACK);

		// ---------- MOUSE ---------- //
		DrawCircleLinesV(player_state.mouse_pos, 5, WHITE);

		// ---------- GRID ---------- //
		Texture2D grid_texture = generateParticleGridTexture(game_grid);
		DrawTexture(grid_texture, 0, 0, WHITE);

	EndDrawing();
	UnloadTexture(grid_texture);
}

int WinMain() {
	main();
}