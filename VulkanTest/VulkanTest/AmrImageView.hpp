#pragma once

#include <vulkan/vulkan.h>

class AmrImageView
{
	VkImageView m_imageView;
	VkDevice m_device;
public:
	
	AmrImageView(const AmrImageView&) = delete;
	AmrImageView(AmrImageView&& other);


	AmrImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	~AmrImageView();

	operator VkImageView() const;

};