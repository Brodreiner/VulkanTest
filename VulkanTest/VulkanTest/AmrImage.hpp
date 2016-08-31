#pragma once

class AmrImage
{
	VkImage m_image = VK_NULL_HANDLE;
	VkDeviceMemory m_deviceMemory = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

	void createImage(const AmrPhysicalDevice& amrPhysicalDevice, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		VkImageCreateInfo imageInfo = {};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = extent.width;
		imageInfo.extent.height = extent.height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(m_device, &imageInfo, nullptr, &m_image) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image!");
		}

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(m_device, m_image, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = amrPhysicalDevice.findMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device, &allocInfo, nullptr, &m_deviceMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate image memory!");
		}

		vkBindImageMemory(m_device, m_image, m_deviceMemory, 0);
	}

public:

	AmrImage()
	{
	}

	AmrImage(const AmrImage&) = delete;
	AmrImage& operator=(const AmrImage&) = delete;
	AmrImage& operator=(AmrImage&& other)
	{
		std::swap(m_image, other.m_image);
		std::swap(m_deviceMemory, other.m_deviceMemory);
		std::swap(m_device, other.m_device);
		return *this;
	}

	AmrImage(const AmrPhysicalDevice& amrPhysicalDevice, VkDevice device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties)
		: m_device(device)
	{
		createImage(amrPhysicalDevice, extent, format, tiling, usage, properties);
	}

	~AmrImage()
	{
		if(m_deviceMemory != VK_NULL_HANDLE)
			vkFreeMemory(m_device, m_deviceMemory, nullptr);
		if (m_image != VK_NULL_HANDLE)
			vkDestroyImage(m_device, m_image, nullptr);
	}

	void writeData(const void* pixels, size_t imageSize)
	{
		if (pixels == nullptr)
			throw std::runtime_error("Texture cannot be copied, because source has no data!");
		if (m_deviceMemory == VK_NULL_HANDLE)
			throw std::runtime_error("Texture cannot be copied, because dest is not alloccated!");
		void* data;
		vkMapMemory(m_device, m_deviceMemory, 0, static_cast<VkDeviceSize>(imageSize), 0, &data);
		memcpy(data, pixels, imageSize);
		vkUnmapMemory(m_device, m_deviceMemory);
	}

	operator VkImage() const
	{
		return m_image;
	}

};