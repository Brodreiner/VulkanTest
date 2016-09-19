#pragma once

#include <vulkan/vulkan.h>

class AmrDebugCallback
{
	VkInstance m_instance = VK_NULL_HANDLE;
	VkDebugReportCallbackEXT m_callback = VK_NULL_HANDLE;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
public:
	AmrDebugCallback() {};
	AmrDebugCallback(const AmrDebugCallback&) = delete;
	AmrDebugCallback(AmrDebugCallback&&) = delete;
	AmrDebugCallback& operator=(const AmrDebugCallback&) = delete;
	AmrDebugCallback& operator=(AmrDebugCallback&& other);

	explicit AmrDebugCallback(VkInstance instance);

	~AmrDebugCallback();


};