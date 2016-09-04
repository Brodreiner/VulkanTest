#pragma once

#include "AmrFramebuffer.hpp"

AmrFramebuffer::AmrFramebuffer(AmrFramebuffer&& other)
	: m_device(other.m_device)
	, m_framebuffer(other.m_framebuffer)
{
	other.m_framebuffer = VK_NULL_HANDLE;
}

AmrFramebuffer::AmrFramebuffer(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& attachments, VkExtent2D extent)
	:m_device(device)
{
	VkFramebufferCreateInfo framebufferInfo = {};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = renderPass;
	framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	framebufferInfo.pAttachments = attachments.data();
	framebufferInfo.width = extent.width;
	framebufferInfo.height = extent.height;
	framebufferInfo.layers = 1;
	if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &m_framebuffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create framebuffer!");
}

AmrFramebuffer::~AmrFramebuffer()
{
	if (m_framebuffer != VK_NULL_HANDLE)
		vkDestroyFramebuffer(m_device, m_framebuffer, nullptr);
}

AmrFramebuffer::operator VkFramebuffer() const
{
	return m_framebuffer;
}
