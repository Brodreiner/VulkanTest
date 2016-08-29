#pragma once

class AmrFramebufferStack
{
	std::vector<AmrFramebuffer> m_framebuffers;

public:
	AmrFramebufferStack(VkDevice device, std::vector<VkImageView> swapChainImageViews, VkImageView depthImageView, VkRenderPass renderPass, VkExtent2D extent)
	{
		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			std::vector<VkImageView> attachments = { swapChainImageViews[i], depthImageView };
			m_framebuffers.emplace_back(device, renderPass, attachments, extent);
		}
	}

};