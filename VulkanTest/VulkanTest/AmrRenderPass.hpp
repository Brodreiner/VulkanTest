#pragma once

#include <vulkan/vulkan.h>

class AmrPhysicalDevice;

class AmrRenderPass
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkRenderPass m_renderPass = VK_NULL_HANDLE;

	void createRenderPass(VkFormat swapChainImageFormat, const AmrPhysicalDevice& amrPhysicalDevice);

public:
	AmrRenderPass() = default;
	AmrRenderPass(const AmrRenderPass&) = delete;
	AmrRenderPass(AmrRenderPass&&) = delete;
	AmrRenderPass& operator=(const AmrRenderPass&) = delete;
	AmrRenderPass& operator=(AmrRenderPass&& other);
	~AmrRenderPass();

	AmrRenderPass(AmrPhysicalDevice amrPhysicalDevice, VkDevice device, VkFormat swapChainImageFormat);

	operator VkRenderPass() const;
};