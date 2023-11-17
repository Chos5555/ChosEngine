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

	VectorFloat();
	VectorFloat(int32_t _x, int32_t _y);

	float_t DotProduct(VectorFloat other);
	float_t Length();
	void Normalize();
};

