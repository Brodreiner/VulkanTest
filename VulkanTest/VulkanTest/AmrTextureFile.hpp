#pragma once

class AmrTextureFile
{
	VkExtent2D m_extent;
	stbi_uc* m_data;
	size_t m_size;

public:
	AmrTextureFile(const std::string& filename)
	{
		int texWidth, texHeight, texChannels;
		m_data = stbi_load(filename.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		m_size = texWidth * texHeight * 4;
		m_extent = { static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight) };
		if (!m_data)
			throw std::runtime_error("failed to load texture '" + filename + "' !");
	}

	~AmrTextureFile()
	{
		stbi_image_free(m_data);
	}

	VkExtent2D extent()
	{
		return m_extent;
	}

	const void* data()
	{
		return m_data;
	}

	const size_t size()
	{
		return m_size;
	}
};