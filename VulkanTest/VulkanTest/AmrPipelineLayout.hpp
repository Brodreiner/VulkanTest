#pragma once

#include <vulkan/vulkan.h>

class AmrPipelineLayout
{
	VkDevice m_device;
	VkPipelineLayout m_pipelineLayout;

public:
	AmrPipelineLayout(const AmrPipelineLayout&) = delete;

	AmrPipelineLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);

	~AmrPipelineLayout();

	operator VkPipelineLayout() const;
};