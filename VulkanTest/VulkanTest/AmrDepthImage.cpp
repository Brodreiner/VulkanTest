#pragma once

#include "AmrDepthImage.hpp"
#include "AmrPhysicalDevice.hpp"
#include "AmrCommandPool.hpp"
#include "AmrFormat.hpp"

AmrDepthImage& AmrDepthImage::operator=(AmrDepthImage&& other)
{
	m_amrDepthFormat = std::move(other.m_amrDepthFormat);
	m_amrDepthImage = std::move(other.m_amrDepthImage);
	m_amrDepthImageView = std::move(other.m_amrDepthImageView);
	return *this;
}

AmrDepthImage::AmrDepthImage(const AmrPhysicalDevice& amrPhysicalDevice, VkQueue graphicsQueue, const AmrCommandPool& commandPool, VkDevice device, VkExtent2D extent)
	: m_amrDepthFormat(amrPhysicalDevice, { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
	, m_amrDepthImage(amrPhysicalDevice, device, extent, m_amrDepthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	, m_amrDepthImageView(device, m_amrDepthImage, m_amrDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT)
{
	commandPool.transitionImageLayout(graphicsQueue, m_amrDepthImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

VkImageView AmrDepthImage::getImageView() const
{
	return m_amrDepthImageView;
}

