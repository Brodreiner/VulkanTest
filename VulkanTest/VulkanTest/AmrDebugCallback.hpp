#pragma once

#include <vulkan/vulkan.h>

class AmrDebugCallback
{
	VkInstance m_instance;
	VkDebugReportCallbackEXT m_callback;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
public:

	explicit AmrDebugCallback(VkInstance instance);

	~AmrDebugCallback();


};