#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorPool
{
	VkDevice m_device;
	VkDescriptorPool m_descriptorPool;

public:
	AmrDescriptorPool(VkDevice device);

	~AmrDescriptorPool();

	operator VkDescriptorPool() const;

};