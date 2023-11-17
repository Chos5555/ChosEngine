

#include "Vector.h"

VectorFloat::VectorFloat(int32_t _x, int32_t _y)
{
	x = (float)_x;
	y = (float)_y;
}

float_t VectorFloat::DotProduct(VectorFloat other)
{
	return (x * other.x) + (y * other.y);
}

float_t VectorFloat::Length()
{
	return sqrtf(DotProduct(*this));
}

void VectorFloat::Normalize()
{
	const float_t length = Length();
	x = x / length;
	y = y / length;
}