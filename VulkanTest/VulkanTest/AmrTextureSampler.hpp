#pragma once

#include <vulkan/vulkan.h>

class AmrTextureSampler
{
	VkSampler m_sampler;
	VkDevice m_device;
public:
	AmrTextureSampler(VkDevice device);

	~AmrTextureSampler();

	operator VkSampler() const;

};