#pragma once

class AmrFramebufferStack
{
	std::vector<AmrFramebuffer> m_framebuffers;
	VkRenderPass m_renderPass;
	VkExtent2D m_extent;

public:
	AmrFramebufferStack(VkDevice device, std::vector<VkImageView> swapChainImageViews, VkImageView depthImageView, VkRenderPass renderPass, VkExtent2D extent)
		: m_renderPass(renderPass)
		, m_extent(extent)
	{
		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			std::vector<VkImageView> attachments = { swapChainImageViews[i], depthImageView };
			m_framebuffers.emplace_back(device, renderPass, attachments, extent);
		}
	}

	size_t size() const
	{
		return m_framebuffers.size();
	}

	const AmrFramebuffer& operator[] (size_t i) const
	{
		return m_framebuffers[i];
	}

	VkRenderPass getRenderPass() const
	{
		return m_renderPass;
	}

	VkExtent2D getExtent() const
	{
		return m_extent;
	}

};