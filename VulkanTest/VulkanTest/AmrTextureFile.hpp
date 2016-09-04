#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <stb_image.h>

class AmrTextureFile
{
	VkExtent2D m_extent;
	stbi_uc* m_data;
	size_t m_size;

public:
	AmrTextureFile(const std::string& filename);

	~AmrTextureFile();

	VkExtent2D extent();

	const void* data();

	const size_t size();
};