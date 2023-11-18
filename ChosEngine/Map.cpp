#include "Map.h"

Map::Map()
{
		size = 8;
		data = new uint8_t[size * size]{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 3, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 4, 4, 0, 1,
    1, 0, 0, 0, 4, 0, 0, 1,
    1, 0, 3, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
        };
        startPosition = *(new VectorFloat(2, 2));
        startDirection = *(new VectorFloat(-1.0f, 0.1f));
        startDirection.Normalize();
        startViewPlane = *(new VectorFloat(0.0f, 0.66f));
}
