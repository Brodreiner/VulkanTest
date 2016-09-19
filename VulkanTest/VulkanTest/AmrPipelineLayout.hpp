#pragma once

#include <vulkan/vulkan.h>

class AmrPipelineLayout
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

public:
	AmrPipelineLayout() = default;
	AmrPipelineLayout(const AmrPipelineLayout&) = delete;
	AmrPipelineLayout(AmrPipelineLayout&&) = delete;
	AmrPipelineLayout& operator=(const AmrPipelineLayout&) = delete;
	AmrPipelineLayout& operator=(AmrPipelineLayout&& other);
	~AmrPipelineLayout();

	AmrPipelineLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);

	operator VkPipelineLayout() const;
};