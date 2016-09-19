#pragma once

#include <vulkan/vulkan.h>

class AmrDescriptorSetLayout
{
	VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrDescriptorSetLayout() {};
	AmrDescriptorSetLayout(const AmrDescriptorSetLayout&) = delete;
	AmrDescriptorSetLayout(AmrDescriptorSetLayout&&) = delete;
	AmrDescriptorSetLayout& operator=(const AmrDescriptorSetLayout&) = delete;
	AmrDescriptorSetLayout& operator=(AmrDescriptorSetLayout&& other);

	AmrDescriptorSetLayout(VkDevice device);

	~AmrDescriptorSetLayout();

	operator VkDescriptorSetLayout() const;
};