#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrQueueFamily
{

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1;
		int presentFamily = -1;
		bool isComplete() const
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	QueueFamilyIndices m_indices;
	std::vector<VkDeviceQueueCreateInfo> m_deviceQueueCreateInfo;
	float m_queuePriority = 1.0f;

	static QueueFamilyIndices findBestQueueFamilieCombination(VkPhysicalDevice device, VkSurfaceKHR surface);

public:
	static bool hasSufficientQueueFamilySupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	AmrQueueFamily() = default;
	AmrQueueFamily(const AmrQueueFamily&) = default;
	AmrQueueFamily(AmrQueueFamily&&) = default;
	AmrQueueFamily& operator=(const AmrQueueFamily&) = default;
	AmrQueueFamily& operator=(AmrQueueFamily&& other) = default;
	~AmrQueueFamily() = default;

	AmrQueueFamily(VkPhysicalDevice device, VkSurfaceKHR surface);

	size_t getDeviceQueueCreateInfoSize() const;

	const VkDeviceQueueCreateInfo* getDeviceQueueCreateInfoData() const;

	uint32_t getGraphicsQueueFamilyIndex() const;

	uint32_t getPresentQueueFamilyIndex() const;

};