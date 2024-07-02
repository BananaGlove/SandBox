#pragma once

#include <raylib.h>
#include "particle_grid.h"
#include "particle.h"

struct PlayerState {
	Vector2 mouse_pos;
	bool is_mouseL_down;
	bool is_mouseR_down;
};

Texture2D generateParticleGridTexture(const ParticleGrid& grid) {
	Image img = GenImageColor(grid.width, grid.height, BLACK);

	for (int x = 0; x < grid.width; x++) {
		for (int y = 0; y < grid.height; y++) {
			uint8_t particle_type = grid.getParticleType(x, y);
			Color particle_color;

			switch (particle_type) {
			case AIR:
				continue;
			case SAND:
				particle_color = YELLOW;
				break;
			default:
				particle_color = RED;
				break;
			}

			ImageDrawPixel(&img, x, y, particle_color);
		}
	}

	return LoadTextureFromImage(img);
}
