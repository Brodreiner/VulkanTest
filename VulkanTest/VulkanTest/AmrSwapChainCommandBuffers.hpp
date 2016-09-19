#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "AmrCommandBuffer.hpp"

#include "AmrFramebufferStack.hpp"

class AmrSwapChainCommandBuffers
{
	std::vector<VkCommandBuffer> m_commandBuffers;
	VkDevice m_device = VK_NULL_HANDLE;
	VkCommandPool m_commandPool = VK_NULL_HANDLE;


public:
	AmrSwapChainCommandBuffers() = default;
	AmrSwapChainCommandBuffers(const AmrSwapChainCommandBuffers&) = delete;
	AmrSwapChainCommandBuffers(AmrSwapChainCommandBuffers&&) = delete;
	AmrSwapChainCommandBuffers& operator=(const AmrSwapChainCommandBuffers&) = delete;
	AmrSwapChainCommandBuffers& operator=(AmrSwapChainCommandBuffers&& other);
	~AmrSwapChainCommandBuffers();

	AmrSwapChainCommandBuffers(VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer, uint32_t indexCount, VkPipelineLayout pipelineLayout, VkDescriptorSet descriptorSet, const AmrFramebufferStack& amrFramebufferStack);

	VkCommandBuffer& operator[](size_t i);
};
