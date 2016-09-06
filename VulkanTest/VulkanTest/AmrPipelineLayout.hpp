#pragma once

#include <vulkan/vulkan.h>

class AmrPipelineLayout
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

public:
	AmrPipelineLayout(const AmrPipelineLayout&) = delete;

	AmrPipelineLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);

	~AmrPipelineLayout();

	operator VkPipelineLayout() const;
};