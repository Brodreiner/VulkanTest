#pragma once

#include <vulkan/vulkan.h>
#include <array>
#include <vector>

class AmrPhysicalDevice
{
	VkPhysicalDevice m_physicalDevice;

	static constexpr std::array<const char*, 1> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	static VkPhysicalDevice pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

	static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

	static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);



	public:
		AmrPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;


		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

		static uint32_t getDeviceExtensionSize();

		static const char* const* getDeviceExtensionData();

		operator VkPhysicalDevice() const;
};