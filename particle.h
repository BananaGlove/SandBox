#pragma once

#include <iostream>
#include <raylib.h>

class Particle {
public:
	Particle(): type(0) {}
	Particle(uint8_t type) : type(type) {}

	uint8_t type;
};

