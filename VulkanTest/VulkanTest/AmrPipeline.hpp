#pragma once

#include <vulkan/vulkan.h>

class AmrPipeline
{
	VkPipeline m_pipeline;
	VkDevice m_device;

public:
	AmrPipeline(const AmrPipeline&) = delete;

	AmrPipeline(VkDevice device, VkExtent2D swapChainExtent, VkPipelineLayout pipelineLayout, VkRenderPass renderPass);

	~AmrPipeline();

	operator VkPipeline() const;

};