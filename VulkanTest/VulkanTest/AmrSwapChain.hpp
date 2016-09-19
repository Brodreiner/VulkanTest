#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "AmrImageView.hpp"

class AmrSwapChain
{
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	std::vector<AmrImageView> m_imageViews;

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	void createSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t graphicsQueueFamilyIndex, uint32_t presentQueueFamilyIndex);

	void createImageViews();

public:
	AmrSwapChain() = default;
	AmrSwapChain(const AmrSwapChain&) = delete;
	AmrSwapChain(AmrSwapChain&&) = delete;
	AmrSwapChain& operator=(const AmrSwapChain&) = delete;
	AmrSwapChain& operator=(AmrSwapChain&& other);
	~AmrSwapChain();

	AmrSwapChain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t graphicsQueueFamilyIndex, uint32_t presentQueueFamilyIndex);

	std::vector<VkImageView> getImageViews();

	VkFormat getImageFormat() const;

	VkExtent2D getExtent() const;

	operator VkSwapchainKHR() const;

};
