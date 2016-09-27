#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "Block.hpp"
#include "LandscapeHeightMap.hpp"
class Chunk
{
	static constexpr size_t SIZE_X = 256;
	static constexpr size_t SIZE_Y = 256;
	static constexpr size_t SIZE_Z = 256;
	static constexpr size_t SIZE = SIZE_X * SIZE_Y * SIZE_Z;

	std::array<Block, SIZE> m_blocks;

public:

	Chunk()
	{
		LandscapeHeightMap<256> landscapeHeightMap;
		size_t index = 0;
		for (size_t x = 0; x < SIZE_X; ++x)
		{
			for (size_t y = 0; y < SIZE_Y; ++y)
			{
				for (size_t z = 0; z < SIZE_Z; ++z)
				{
					if (y == landscapeHeightMap.getNormalized(x, z))
						m_blocks[index].setType(BLOCK_TYPE::DIRT);
					++index;
				}
			}
		}
	}

	static glm::vec3 getCenterPoint()
	{
		float x = SIZE_X / 2.f;
		float y = SIZE_Y / 2.f;
		float z = SIZE_Z / 2.f;
		return glm::vec3{ x,y,z };
	}

	void draw(std::vector<AmrVertex>& vertexContainer, std::vector<uint32_t>& indexContainer)
	{
		size_t index = 0;
		for (size_t x = 0; x < SIZE_X; ++x)
		{
			for (size_t y = 0; y < SIZE_Y; ++y)
			{
				for (size_t z = 0; z < SIZE_Z; ++z)
				{
					glm::vec3 offset{ x,y,z };
					if(y == SIZE_Y - 1 || m_blocks[index + SIZE_Z].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::TOP);
					if (y == 0 || m_blocks[index - SIZE_Z].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::BOTTOM);
					if (z == SIZE_Z - 1 || m_blocks[index + 1].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::FRONT);
					if (z == 0 || m_blocks[index - 1].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::BACK);
					if (x == 0 || m_blocks[index - SIZE_Y * SIZE_Z].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::LEFT);
					if (x == SIZE_X - 1 || m_blocks[index + SIZE_Y * SIZE_Z].isTransparent())
						m_blocks[index].drawFace(vertexContainer, indexContainer, offset, FACE::RIGHT);
					++index;
				}
			}
		}
	}


};
