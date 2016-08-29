#pragma once

class AmrFormat
{
	VkFormat m_format;
public:

	AmrFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
	{
		for (VkFormat format : candidates) {
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
			{
				m_format = format;
				return;
			}
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			{
				m_format = format;
				return;
			}
		}
		throw std::runtime_error("failed to find supported format!");
	}

	operator VkFormat() const
	{
		return m_format;
	}

};