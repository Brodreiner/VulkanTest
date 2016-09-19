#pragma once

#include <vulkan/vulkan.h>

class AmrTextureSampler
{
	VkSampler m_sampler = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
public:
	AmrTextureSampler() = default;
	AmrTextureSampler(const AmrTextureSampler&) = delete;
	AmrTextureSampler(AmrTextureSampler&&) = delete;
	AmrTextureSampler& operator=(const AmrTextureSampler&) = delete;
	AmrTextureSampler& operator=(AmrTextureSampler&& other);
	~AmrTextureSampler();

	AmrTextureSampler(VkDevice device);

	operator VkSampler() const;

};