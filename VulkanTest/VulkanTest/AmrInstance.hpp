#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrInstance {
	VkInstance m_instance;

	static std::vector<const char*> getRequiredExtensions();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);


public:
	AmrInstance();

	~AmrInstance();

	operator VkInstance() const;
};

