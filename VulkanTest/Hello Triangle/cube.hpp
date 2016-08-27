#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


glm::vec3 RED = { 1.0f, 0.0f, 0.0f };
glm::vec3 GREEN = { 0.0f, 1.0f, 0.0f };
glm::vec3 BLUE = { 0.0f, 0.0f, 1.0f };
glm::vec3 MAGENTA = { 1.0f, 0.0f, 1.0f };

//std::vector<Vertex> vertices = {
//	//{ { -0.5f, -0.5f, 0.5f },RED },
//	//{ { 0.5f, -0.5f, 0.5f },GREEN },
//	//{ { 0.5f, 0.5f, 0.5f },BLUE },
//	//{ { -0.5f, 0.5f, 0.5f },MAGENTA },
//	//{ { -0.5f, -0.5f, -0.5f },RED },
//	//{ { 0.5f, -0.5f, -0.5f },GREEN },
//	//{ { 0.5f, 0.5f, -0.5f },BLUE },
//	//{ { -0.5f, 0.5f, -0.5f },MAGENTA },
//};
//
//std::vector<uint32_t> indices = {
//	//0, 1, 2, 2, 3, 0,
//	//4, 5, 6, 6, 7, 4,
//	//0,4,1,1,4,5,
//	//1,5,2,2,5,6,
//	//2,6,3,3,6,7,
//	//3,7,0,0,7,4,
//
//};


std::vector<Vertex> vertices = {
	//{ { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//{ { 0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { -0.5f, 0.5f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },

	//{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//{ { 0.5f, 0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { -0.5f, 0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
};

std::vector<uint32_t> indices = {
	//0, 1, 2, 2, 3, 0,
	//4, 5, 6, 6, 7, 4
};


void addCube(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glm::vec3 center, float size)
{
	const std::array<uint32_t, 6 * 6> indexArray = {
		0, 1, 2, 2, 3, 0,
		4, 6, 5, 6, 4, 7,
		0, 4, 1, 1, 4, 5,
		1, 5, 2, 2, 5, 6,
		2, 6, 3, 3, 6, 7,
		3, 7, 0, 0, 7, 4,
	};
	for (auto index : indexArray)
	{
		indices.push_back(static_cast<uint32_t>(vertices.size()) + index);
	}

	size /= 2;
	vertices.push_back({ { center[0] - size , center[1] - size , center[2] + size },{ 0.2f, 0.2f, 0.2f }, { 0.0f, 0.0f } });
	vertices.push_back({ { center[0] + size , center[1] - size , center[2] + size },{ 0.2f, 0.2f, 0.8f }, { 1.0f, 0.0f } });
	vertices.push_back({ { center[0] + size , center[1] + size , center[2] + size },{ 0.2f, 0.8f, 0.2f }, { 1.0f, 1.0f } });
	vertices.push_back({ { center[0] - size , center[1] + size , center[2] + size },{ 0.2f, 0.8f, 0.8f }, { 0.0f, 1.0f } });
	vertices.push_back({ { center[0] - size , center[1] - size , center[2] - size },{ 0.8f, 0.2f, 0.2f }, { 0.0f, 0.0f } });
	vertices.push_back({ { center[0] + size , center[1] - size , center[2] - size },{ 0.8f, 0.2f, 0.8f }, { 1.0f, 0.0f } });
	vertices.push_back({ { center[0] + size , center[1] + size , center[2] - size },{ 0.8f, 0.8f, 0.2f }, { 1.0f, 1.0f } });
	vertices.push_back({ { center[0] - size , center[1] + size , center[2] - size },{ 0.8f, 0.8f, 0.8f }, { 0.0f, 1.0f } });
}

void addCubes(int numPerEdge)
{
	//indices.push_back(0);
	//indices.push_back(1);
	//indices.push_back(2);
	//vertices.push_back({ { -0.5f , -0.5f , -0.5f },{ 0.2f, 0.2f, 0.2f },{ 0.0f, 0.0f } });
	//vertices.push_back({ { +0.5f , -0.5f , -0.5f },{ 0.2f, 0.2f, 0.8f },{ 1.0f, 0.0f } });
	//vertices.push_back({ { +0.5f , +0.5f , -0.5f },{ 0.2f, 0.8f, 0.2f },{ 1.0f, 1.0f } });
	//return;


	for (int x = 0; x < numPerEdge; ++x)
	{
		for (int y = 0; y < numPerEdge; ++y)
		{
			for (int z = 0; z < numPerEdge; ++z)
			{
				float size = 1.0f / numPerEdge;
				glm::vec3 center{ x * size - ((numPerEdge-1)*size/2), y * size - ((numPerEdge - 1)*size / 2), z * size - ((numPerEdge - 1)*size / 2) };
				addCube(vertices, indices, center, size);
			}
		}
	}
}
