#pragma once

#include <vulkan/vulkan.h>

class AmrPipeline
{
	VkPipeline m_pipeline = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrPipeline(const AmrPipeline&) = delete;

	AmrPipeline(VkDevice device, VkExtent2D swapChainExtent, VkPipelineLayout pipelineLayout, VkRenderPass renderPass);

	~AmrPipeline();

	operator VkPipeline() const;

};