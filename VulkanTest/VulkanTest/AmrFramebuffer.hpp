#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrFramebuffer
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkFramebuffer m_framebuffer = VK_NULL_HANDLE;

public:
	AmrFramebuffer(const AmrFramebuffer&) = delete;
	AmrFramebuffer(AmrFramebuffer&& other);

	AmrFramebuffer(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& attachments, VkExtent2D extent);

	~AmrFramebuffer();

	operator VkFramebuffer() const;

};