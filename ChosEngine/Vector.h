#pragma once

#include <math.h>
#include <stdint.h>

class VectorInt
{
public:
	int32_t x;
	int32_t y;
};

class VectorFloat
{
public:
	float_t x;
	float_t y;

	VectorFloat(int _x, int _y) { x = (float)_x; y = (float)_y; }
};

