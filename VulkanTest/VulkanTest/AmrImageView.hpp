#pragma once

#include <vulkan/vulkan.h>

class AmrImageView
{
	VkImageView m_imageView = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
public:
	
	AmrImageView(const AmrImageView&) = delete;
	AmrImageView(AmrImageView&& other);


	AmrImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	~AmrImageView();

	operator VkImageView() const;

};