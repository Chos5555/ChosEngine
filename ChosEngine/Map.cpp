#include "Map.h"

Map::Map(char* input)
{
	if (input == "test")
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
        startPosition = *(new VectorFloat(2, 2))
	}
    else
    {
        size = 0;
        data = new uint8_t[0];
    }
}
