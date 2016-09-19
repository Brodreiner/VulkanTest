#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrFormat
{
	VkFormat m_format = VK_FORMAT_UNDEFINED;
public:

	AmrFormat() {};
	AmrFormat(const AmrFormat&) = delete;
	AmrFormat(AmrFormat&&) = delete;
	AmrFormat& operator=(const AmrFormat&) = delete;
	AmrFormat& operator=(AmrFormat&& other);

	AmrFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	operator VkFormat() const;

};
