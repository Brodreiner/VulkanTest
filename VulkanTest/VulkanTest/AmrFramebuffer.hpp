#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrFramebuffer
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkFramebuffer m_framebuffer = VK_NULL_HANDLE;

public:
	AmrFramebuffer() {};
	AmrFramebuffer(const AmrFramebuffer&) = delete;
	AmrFramebuffer(AmrFramebuffer&&);
	AmrFramebuffer& operator=(const AmrFramebuffer&) = delete;
	AmrFramebuffer& operator=(AmrFramebuffer&& other);

	AmrFramebuffer(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& attachments, VkExtent2D extent);

	~AmrFramebuffer();

	operator VkFramebuffer() const;

};