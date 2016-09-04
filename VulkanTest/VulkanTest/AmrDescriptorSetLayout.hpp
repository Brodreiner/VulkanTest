#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorSetLayout
{
	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDevice m_device;

public:
	AmrDescriptorSetLayout(const AmrDescriptorSetLayout&) = delete;

	AmrDescriptorSetLayout(VkDevice device);

	~AmrDescriptorSetLayout();

	operator VkDescriptorSetLayout() const;
};