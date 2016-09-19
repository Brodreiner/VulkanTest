#pragma once

#include <vulkan/vulkan.h>

class AmrImageView
{
	VkImageView m_imageView = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
public:
	
	AmrImageView() = default;
	AmrImageView(const AmrImageView&) = delete;
	AmrImageView(AmrImageView&&);
	AmrImageView& operator=(const AmrImageView&) = delete;
	AmrImageView& operator=(AmrImageView&& other);
	~AmrImageView();

	AmrImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);


	operator VkImageView() const;

};