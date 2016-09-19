#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorPool
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;

public:
	AmrDescriptorPool() {};
	AmrDescriptorPool(const AmrDescriptorPool&) = delete;
	AmrDescriptorPool(AmrDescriptorPool&&) = delete;
	AmrDescriptorPool& operator=(const AmrDescriptorPool&) = delete;
	AmrDescriptorPool& operator=(AmrDescriptorPool&& other);

	AmrDescriptorPool(VkDevice device);

	~AmrDescriptorPool();

	operator VkDescriptorPool() const;

};