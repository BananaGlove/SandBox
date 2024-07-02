#include "particle_grid.h"

ParticleGrid::ParticleGrid(const int width, const int height) : width(width), height(height) {
	_grid = new Particle*[width];

	for (int i = 0; i < width; i++) {
		_grid[i] = new Particle[height];

		for (int j = 0; j < height; j++) {
			_grid[i][j] = Particle{AIR};
		}
	}
}
ParticleGrid::~ParticleGrid() {
	delete[] _grid;
}



// ---------- IN BOUND ---------- //
bool ParticleGrid::isInBound(int x, int y) const {
	return x >= 0 && x < width && y >= 0 && y < height;
}
bool ParticleGrid::isInBound(Vector2 pos) const {
	return isInBound(pos.x, pos.y);
}



// ---------- GETTERS ---------- //
Particle ParticleGrid::getParticle(int x, int y) const {
	return _grid[x][y];
}
Particle ParticleGrid::getParticle(Vector2 pos) const {
	return getParticle(pos.x, pos.y);
}
uint8_t ParticleGrid::getParticleType(int x, int y) const {
	return getParticle(x, y).type;
}
uint8_t ParticleGrid::getParticleType(Vector2 pos) const {
	return getParticle(pos).type;
}



// ---------- SETTERS ---------- //
void ParticleGrid::setParticle(int x, int y, Particle new_particle) {
	_grid[x][y] = new_particle;
}
void ParticleGrid::setParticle(Vector2 pos, Particle new_particle) {
	setParticle(pos.x, pos.y, new_particle);
}

void ParticleGrid::setParticleType(int x, int y, uint8_t new_particle_type) {
	_grid[x][y].type = new_particle_type;
}

void ParticleGrid::setParticleType(Vector2 pos, uint8_t new_particle_type) {
	setParticleType(pos.x, pos.y, new_particle_type);
}



void ParticleGrid::drawParticles(const Brush& brush, Vector2 mouse_pos) {
	const uint32_t brush_size = brush.getSize();
	const uint32_t brush_type = brush.getType();
	const BrushShape& brush_shape = brush.getShape();

	for (int x = mouse_pos.x - brush_size; x <= mouse_pos.x + brush_size; x++) {
		for (int y = mouse_pos.y - brush_size; y <= mouse_pos.y + brush_size; y++) {
			Vector2 particle_pos{ (float)x, (float)y };
			uint8_t particle_type = getParticleType(particle_pos);

			if (particle_type != brush_type && (particle_type == AIR || brush_type == AIR) 
				&& isInBound(particle_pos) && brush_shape.check(mouse_pos, particle_pos, brush_size)) {

				setParticleType(particle_pos, brush_type);
			}
		}
	}
}


const Vector2 offsets[] = { // Ordered by priority
	{0, 1}, {-1, 1}, {1, 1}
};

void ParticleGrid::updateAllParticles() {
	for (int x = 0; x < width; x++) {
		for (int y = height; y >= 0; y--) {
			uint8_t particle_type = getParticleType(x, y);
			if (particle_type == AIR) continue;

			for (Vector2 offset : offsets) {
				Vector2 new_pos{ x + offset.x, y + offset.y };

				if (isInBound(new_pos) && getParticleType(new_pos) == AIR) {
					setParticleType(new_pos, particle_type);
					setParticleType(x, y, AIR);
					break;
				}
			}
		}
	}
}
