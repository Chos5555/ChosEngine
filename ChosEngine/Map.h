#pragma once

#include <stdint.h>

#include "Vector.h"

class Map
{
public:
	Map() {};
	Map(const char* fileName);

	uint16_t size;
	uint8_t* data;
	VectorFloat startPosition;
	VectorFloat startDirection;
	VectorFloat startViewPlane;

private:

	void LoadFromFile(const char* name);
};