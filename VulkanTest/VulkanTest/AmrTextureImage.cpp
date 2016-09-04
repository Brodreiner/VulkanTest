#pragma once

#include "AmrTextureImage.hpp"
#include "AmrPhysicalDevice.hpp"
#include "AmrCommandPool.hpp"
#include "AmrTextureFile.hpp"
#include "AmrImage.hpp"

AmrTextureImage::AmrTextureImage(const AmrPhysicalDevice& amrPhysicalDevice, VkDevice device, const AmrCommandPool& commandPool, VkQueue graphicsQueue, const std::string& filename)
{
	AmrTextureFile amrTextureFile(filename);
	AmrImage stagingImage(amrPhysicalDevice, device, amrTextureFile.extent(), VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingImage.writeData(amrTextureFile.data(), amrTextureFile.size());
	m_textureImage = AmrImage(amrPhysicalDevice, device, amrTextureFile.extent(), VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	commandPool.transitionImageLayout(graphicsQueue, stagingImage, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
	commandPool.transitionImageLayout(graphicsQueue, m_textureImage, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	commandPool.copyImage(graphicsQueue, stagingImage, m_textureImage, amrTextureFile.extent());
	commandPool.transitionImageLayout(graphicsQueue, m_textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

AmrTextureImage::operator VkImage() const
{
	return m_textureImage;
}
