#pragma once

#include <vulkan/vulkan.h>

#include "AmrFormat.hpp"
#include "AmrImage.hpp"
#include "AmrImageView.hpp"

class AmrCommandPool;
class AmrPhysicalDevice;

class AmrDepthImage
{
	AmrFormat m_amrDepthFormat;
	AmrImage m_amrDepthImage;
	AmrImageView m_amrDepthImageView;

public:
	AmrDepthImage() {};
	AmrDepthImage(const AmrDepthImage&) = delete;
	AmrDepthImage(AmrDepthImage&&) = delete;
	AmrDepthImage& operator=(const AmrDepthImage&) = delete;
	AmrDepthImage& operator=(AmrDepthImage&& other);

	AmrDepthImage(const AmrPhysicalDevice& amrPhysicalDevice, VkQueue graphicsQueue, const AmrCommandPool& commandPool, VkDevice device, VkExtent2D extent);
	
	VkImageView getImageView() const;

};