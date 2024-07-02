#pragma once

#include <iostream>
#include <raylib.h>
#include <array>

#include "particle.h"
#include "brush.h"

constexpr uint8_t AIR = 0;
constexpr uint8_t SAND = 1;

class ParticleGrid {
public:
	const int width;
	const int height;

	ParticleGrid(int width, int height);
	~ParticleGrid();

	bool isInBound(int x, int y) const;
	bool isInBound(Vector2 pos) const;

	Particle getParticle(int x, int y) const;
	Particle getParticle(Vector2 pos) const;
	uint8_t getParticleType(int x, int y) const;
	uint8_t getParticleType(Vector2 pos) const;

	void setParticle(int x, int y, Particle new_particle);
	void setParticle(Vector2 pos, Particle new_particle);
	void setParticleType(int x, int y, uint8_t new_particle_type);
	void setParticleType(Vector2 pos, uint8_t new_particle_type);

	void drawParticles(const Brush& brush, Vector2 mouse_pos);
	void updateAllParticles();

private:
	Particle** _grid;
};

