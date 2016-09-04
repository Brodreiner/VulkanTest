#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrFramebuffer;

class AmrFramebufferStack
{
	std::vector<AmrFramebuffer> m_framebuffers;
	VkRenderPass m_renderPass;
	VkExtent2D m_extent;

public:
	AmrFramebufferStack(VkDevice device, std::vector<VkImageView> swapChainImageViews, VkImageView depthImageView, VkRenderPass renderPass, VkExtent2D extent);

	size_t size() const;

	const AmrFramebuffer& operator[] (size_t i) const;

	VkRenderPass getRenderPass() const;

	VkExtent2D getExtent() const;

};