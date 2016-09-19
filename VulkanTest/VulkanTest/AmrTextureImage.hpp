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
	AmrTextureImage() = default;
	AmrTextureImage(const AmrTextureImage&) = default;
	AmrTextureImage(AmrTextureImage&&) = default;
	AmrTextureImage& operator=(const AmrTextureImage&) = default;
	AmrTextureImage& operator=(AmrTextureImage&& other) = default;
	~AmrTextureImage() = default;

	AmrTextureImage(const AmrPhysicalDevice& amrPhysicalDevice, VkDevice device, const AmrCommandPool& commandPool, VkQueue graphicsQueue, const std::string& filename);

	operator VkImage() const;
};
