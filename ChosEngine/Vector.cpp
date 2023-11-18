#include "Vector.h"

VectorFloat::VectorFloat()
{
	x = 0.0f;
	y = 0.0f;
}

VectorFloat::VectorFloat(float_t _x, float_t _y)
{
	x = _x;
	y = _y;
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