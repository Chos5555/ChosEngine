#include "Map.h"

Map::Map(char* input)
{
	if (input == "test")
	{
		Size = 8;
		Data = new uint8_t[Size * Size]{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 3, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 4, 4, 0, 1,
    1, 0, 0, 0, 4, 0, 0, 1,
    1, 0, 3, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
        };
	}
    else
    {
        Size = 0;
        Data = new uint8_t[0];
    }
}
