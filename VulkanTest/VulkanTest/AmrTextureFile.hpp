#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <stb_image.h>

class AmrTextureFile
{
	VkExtent2D m_extent = { 0, 0 };
	stbi_uc* m_data = nullptr;
	size_t m_size = 0;

public:
	AmrTextureFile(const std::string& filename);

	~AmrTextureFile();

	VkExtent2D extent();

	const void* data();

	const size_t size();
};