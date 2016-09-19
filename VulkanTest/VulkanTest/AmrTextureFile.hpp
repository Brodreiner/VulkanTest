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
	AmrTextureFile() = default;
	AmrTextureFile(const AmrTextureFile&) = delete;
	AmrTextureFile(AmrTextureFile&&) = delete;
	AmrTextureFile& operator=(const AmrTextureFile&) = delete;
	AmrTextureFile& operator=(AmrTextureFile&& other);
	~AmrTextureFile();

	AmrTextureFile(const std::string& filename);

	VkExtent2D extent();

	const void* data();

	const size_t size();
};