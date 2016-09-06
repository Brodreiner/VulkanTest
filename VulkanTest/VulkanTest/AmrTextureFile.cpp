#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "AmrTextureFile.hpp"
#include <string>

AmrTextureFile::AmrTextureFile(const std::string& filename)
{
	int texWidth, texHeight, texChannels;
	m_data = stbi_load(filename.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	m_size = texWidth * texHeight * 4;
	m_extent = { static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight) };
	if (!m_data)
		throw std::runtime_error("failed to load texture '" + filename + "' !");
}

AmrTextureFile::~AmrTextureFile()
{
	if (m_data != nullptr)
		stbi_image_free(m_data);
}

VkExtent2D AmrTextureFile::extent()
{
	return m_extent;
}

const void* AmrTextureFile::data()
{
	return m_data;
}

const size_t AmrTextureFile::size()
{
	return m_size;
}
