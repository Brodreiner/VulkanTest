#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorPool
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;

public:
	AmrDescriptorPool(VkDevice device);

	~AmrDescriptorPool();

	operator VkDescriptorPool() const;

};