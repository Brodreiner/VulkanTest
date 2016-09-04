#pragma once

#include <vulkan/vulkan.h>

class AmrPhysicalDevice;

class AmrRenderPass
{
	VkDevice m_device;
	VkRenderPass m_renderPass;

	void createRenderPass(VkFormat swapChainImageFormat, const AmrPhysicalDevice& amrPhysicalDevice);

public:
	AmrRenderPass(AmrPhysicalDevice amrPhysicalDevice, VkDevice device, VkFormat swapChainImageFormat);

	~AmrRenderPass();

	operator VkRenderPass() const;
};