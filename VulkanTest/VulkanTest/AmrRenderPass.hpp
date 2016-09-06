#pragma once

#include <vulkan/vulkan.h>

class AmrPhysicalDevice;

class AmrRenderPass
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkRenderPass m_renderPass = VK_NULL_HANDLE;

	void createRenderPass(VkFormat swapChainImageFormat, const AmrPhysicalDevice& amrPhysicalDevice);

public:
	AmrRenderPass(AmrPhysicalDevice amrPhysicalDevice, VkDevice device, VkFormat swapChainImageFormat);

	~AmrRenderPass();

	operator VkRenderPass() const;
};