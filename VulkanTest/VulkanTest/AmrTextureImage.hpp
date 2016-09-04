#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include "AmrImage.hpp"

class AmrPhysicalDevice;
class AmrCommandPool;


class AmrTextureImage
{
	AmrImage m_textureImage;
public:
	AmrTextureImage(const AmrPhysicalDevice& amrPhysicalDevice, VkDevice device, const AmrCommandPool& commandPool, VkQueue graphicsQueue, const std::string& filename);

	operator VkImage() const;
};
