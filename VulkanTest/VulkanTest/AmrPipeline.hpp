#pragma once

#include <vulkan/vulkan.h>

class AmrPipeline
{
	VkPipeline m_pipeline = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrPipeline() = default;
	AmrPipeline(const AmrPipeline&) = delete;
	AmrPipeline(AmrPipeline&&) = delete;
	AmrPipeline& operator=(const AmrPipeline&) = delete;
	AmrPipeline& operator=(AmrPipeline&& other);
	~AmrPipeline();

	AmrPipeline(VkDevice device, VkExtent2D swapChainExtent, VkPipelineLayout pipelineLayout, VkRenderPass renderPass);

	operator VkPipeline() const;

};