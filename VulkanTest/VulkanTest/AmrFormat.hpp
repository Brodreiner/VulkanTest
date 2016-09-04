#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrFormat
{
	VkFormat m_format;
public:

	AmrFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	operator VkFormat() const;

};