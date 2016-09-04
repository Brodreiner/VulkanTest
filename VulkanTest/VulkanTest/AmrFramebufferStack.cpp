#pragma once

#include "AmrFramebufferStack.hpp"
#include "AmrFramebuffer.hpp"


AmrFramebufferStack::AmrFramebufferStack(VkDevice device, std::vector<VkImageView> swapChainImageViews, VkImageView depthImageView, VkRenderPass renderPass, VkExtent2D extent)
	: m_renderPass(renderPass)
	, m_extent(extent)
{
	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{
		std::vector<VkImageView> attachments = { swapChainImageViews[i], depthImageView };
		m_framebuffers.emplace_back(device, renderPass, attachments, extent);
	}
}

size_t AmrFramebufferStack::size() const
{
	return m_framebuffers.size();
}

const AmrFramebuffer& AmrFramebufferStack::operator[] (size_t i) const
{
	return m_framebuffers[i];
}

VkRenderPass AmrFramebufferStack::getRenderPass() const
{
	return m_renderPass;
}

VkExtent2D AmrFramebufferStack::getExtent() const
{
	return m_extent;
}
