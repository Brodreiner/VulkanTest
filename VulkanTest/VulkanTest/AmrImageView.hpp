#pragma once

class AmrImageView
{
	VkImageView m_imageView;
	VkDevice m_device;
public:
	
	AmrImageView(const AmrImageView&) = delete;
	AmrImageView(AmrImageView&& other)
		: m_imageView(other.m_imageView)
		, m_device(other.m_device)
	{
		other.m_imageView = VK_NULL_HANDLE;
	}


	AmrImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
		:m_device(device)
	{
		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = image;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;
		if (vkCreateImageView(m_device, &viewInfo, nullptr, &m_imageView) != VK_SUCCESS)
			throw std::runtime_error("failed to create texture image view!");
	}

	~AmrImageView()
	{
		if(m_imageView != VK_NULL_HANDLE)
			vkDestroyImageView(m_device, m_imageView, nullptr);
	}

};