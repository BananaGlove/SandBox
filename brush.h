#pragma once

#include <iostream>
#include <raylib.h>
#include <raymath.h>

class BrushShape {
public:
	virtual bool check(Vector2 mouse_pos, Vector2 particle_pos, uint32_t size) const = NULL;
private:
};

class SquareBrush: public BrushShape {
public:
	bool check(Vector2 mouse_pos, Vector2 particle_pos, uint32_t size) const override {
		return true;
	}
};

class CircleBrush : public BrushShape {
public:
	bool check(Vector2 mouse_pos, Vector2 particle_pos, uint32_t size) const override {
		return Vector2Distance(mouse_pos, particle_pos) <= size;
	}
};

class Brush {
public:
	Brush(uint8_t particle_type, uint32_t size, std::shared_ptr<BrushShape> shape) : m_particle_type(particle_type), m_size(size), m_shape(std::move(shape)) {}

	const uint8_t getType() const { return m_particle_type; }
	const uint32_t getSize() const { return m_size; }
	const BrushShape& getShape() const { return *m_shape; }

private:
	uint8_t m_particle_type;
	uint32_t m_size;
	std::shared_ptr<BrushShape> m_shape;
};

