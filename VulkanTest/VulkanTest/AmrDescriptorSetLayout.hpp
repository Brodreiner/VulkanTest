#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorSetLayout
{
	VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrDescriptorSetLayout(const AmrDescriptorSetLayout&) = delete;

	AmrDescriptorSetLayout(VkDevice device);

	~AmrDescriptorSetLayout();

	operator VkDescriptorSetLayout() const;
};