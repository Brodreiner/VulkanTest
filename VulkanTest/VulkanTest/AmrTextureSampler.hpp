#pragma once

#include <vulkan/vulkan.h>

class AmrTextureSampler
{
	VkSampler m_sampler = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
public:
	AmrTextureSampler(VkDevice device);

	~AmrTextureSampler();

	operator VkSampler() const;

};