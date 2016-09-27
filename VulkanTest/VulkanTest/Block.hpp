#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include "AmrVertex.hpp"

#include <glm/vec3.hpp>

enum class FACE
{
	TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT
};

enum class BLOCK_TYPE : uint8_t
{
	AIR  = 0b00000000,
	DIRT = 0b00000001,
};


const std::vector<AmrVertex> v = { {
		// top
		{ { 0.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 0.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 1.f, 1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 1.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		// bottom
		{ { 0.f, 0.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 1.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ { 1.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 0.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		// front
		{ { 0.f, 1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 0.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 1.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 1.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		// back
		{ { 1.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 1.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 0.f, 0.f, 0.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 0.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		// left
		{ { 0.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 0.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 0.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 0.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		// right
		{ { 1.f, 1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ { 1.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 1.f, 0.f, 0.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { 1.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	} };

class Block
{

	BLOCK_TYPE m_type = BLOCK_TYPE::AIR;

public:
	bool isTransparent()
	{
		return !static_cast<uint8_t>(m_type) & 0x01; // least significant bit is transparency
	}

	void setType(BLOCK_TYPE type)
	{
		m_type = type;
	}

	void drawFace(std::vector<AmrVertex>& vertexContainer, std::vector<uint32_t>& indexContainer, glm::vec3& offset, FACE face)
	{
		if (m_type == BLOCK_TYPE::AIR)
			return;
		switch (face)
		{
		case FACE::TOP:
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 0.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 1.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			break;
		case FACE::BOTTOM:
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 0.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			break;
		case FACE::FRONT:
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 1.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			break;
		case FACE::BACK:
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 0.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 0.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			break;
		case FACE::LEFT:
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 0.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 0.f, 1.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			break;
		case FACE::RIGHT:
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 1.f } +offset,glm::vec3{ 1.0f, 0.0f, 0.0f } +offset,glm::vec2{ 0.0f, 0.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 1.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 0.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 0.f, 0.f } +offset,glm::vec3{ 0.0f, 0.0f, 1.0f } +offset,glm::vec2{ 1.0f, 1.0f } });
			vertexContainer.push_back({ glm::vec3{ 1.f, 1.f, 0.f } +offset,glm::vec3{ 0.0f, 1.0f, 0.0f } +offset,glm::vec2{ 1.0f, 0.0f } });
			break;
		}
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 4));
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 3));
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 2));
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 2));
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 1));
		indexContainer.push_back(static_cast<uint32_t>(vertexContainer.size() - 4));
	}

	//void drawAllFaces(std::vector<AmrVertex>& vertexContainer, std::vector<uint32_t>& indexContainer, glm::vec3& offset)
	//{
	//	drawFace(vertexContainer, indexContainer, offset, FACE::TOP);
	//	drawFace(vertexContainer, indexContainer, offset, FACE::BOTTOM);
	//	drawFace(vertexContainer, indexContainer, offset, FACE::FRONT);
	//	drawFace(vertexContainer, indexContainer, offset, FACE::BACK);
	//	drawFace(vertexContainer, indexContainer, offset, FACE::LEFT);
	//	drawFace(vertexContainer, indexContainer, offset, FACE::RIGHT);
	//}

};