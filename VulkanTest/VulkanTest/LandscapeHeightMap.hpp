#pragma once
#include <array>
#include <cmath>

template <size_t SIZE>
class LandscapeHeightMap
{
	uint32_t values[SIZE][SIZE];
public:
	LandscapeHeightMap()
	{
		for (auto x = 0; x < SIZE; ++x)
		{
			for (auto z = 0; z < SIZE; ++z)
			{
				values[x][z] = sqrt(x*x + z*z);
			}
		}
	}

	size_t getNormalized(size_t x, size_t z)
	{
		return values[x][z];
	}
};
