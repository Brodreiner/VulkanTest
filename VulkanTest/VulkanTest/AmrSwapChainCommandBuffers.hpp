#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "AmrCommandBuffer.hpp"

#include "AmrFramebufferStack.hpp"

class AmrSwapChainCommandBuffers
{
	std::vector<VkCommandBuffer> m_commandBuffers;
	VkDevice m_device;
	VkCommandPool m_commandPool;


public:

	AmrSwapChainCommandBuffers(VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer, uint32_t indexCount, VkPipelineLayout pipelineLayout, VkDescriptorSet descriptorSet, const AmrFramebufferStack& amrFramebufferStack);

	~AmrSwapChainCommandBuffers();

	VkCommandBuffer& operator[](size_t i);
};
