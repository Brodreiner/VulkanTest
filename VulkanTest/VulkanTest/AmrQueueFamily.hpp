#pragma once

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

	static QueueFamilyIndices findBestQueueFamilieCombination(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (queueFamily.queueCount > 0 && presentSupport) {
				indices.presentFamily = i;
			}
			if (indices.isComplete()) {
				break;
			}
			i++;
		}
		return indices;
	}

	QueueFamilyIndices m_indices;
	std::vector<VkDeviceQueueCreateInfo> m_deviceQueueCreateInfo;
	float m_queuePriority = 1.0f;
public:
	static bool hasSufficientQueueFamilySupport(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices = findBestQueueFamilieCombination(device, surface);
		return indices.isComplete();
	}

	AmrQueueFamily(VkPhysicalDevice device, VkSurfaceKHR surface)
	:m_indices(findBestQueueFamilieCombination(device, surface))
	{
		if (!m_indices.isComplete())
			throw std::runtime_error("No sufficient QueueFamilie support found!");
		VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
		deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueCreateInfo.queueFamilyIndex = m_indices.graphicsFamily;
		deviceQueueCreateInfo.queueCount = 1;
		deviceQueueCreateInfo.pQueuePriorities = &m_queuePriority;
		m_deviceQueueCreateInfo.push_back(deviceQueueCreateInfo);
		// if graphics an present queue family are not the same, add both of them
		if (m_indices.presentFamily != m_indices.graphicsFamily)
		{
			deviceQueueCreateInfo.queueFamilyIndex = m_indices.presentFamily;
			m_deviceQueueCreateInfo.push_back(deviceQueueCreateInfo);
		}
	}

	size_t getDeviceQueueCreateInfoSize() const
	{
		return m_deviceQueueCreateInfo.size();
	}

	const VkDeviceQueueCreateInfo* getDeviceQueueCreateInfoData() const
	{
		return m_deviceQueueCreateInfo.data();
	}

	uint32_t getGraphicsQueueFamilyIndex() const
	{
		return m_indices.graphicsFamily;
	}

	uint32_t getPresentQueueFamilyIndex() const
	{
		return m_indices.presentFamily;
	}

};