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
	AmrDepthImage(const AmrPhysicalDevice& amrPhysicalDevice, VkQueue graphicsQueue, const AmrCommandPool& commandPool, VkDevice device, VkExtent2D extent);
	
	VkImageView getImageView() const;

};