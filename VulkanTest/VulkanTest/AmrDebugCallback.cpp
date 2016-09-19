#pragma once

#include "AmrDebugCallback.hpp"
#include <iostream>

VKAPI_ATTR VkBool32 VKAPI_CALL AmrDebugCallback::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	std::cerr << "validation layer: " << msg << std::endl;
	return VK_FALSE;
}

AmrDebugCallback& AmrDebugCallback::operator=(AmrDebugCallback&& other)
{
	if (m_instance != VK_NULL_HANDLE)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr)
		{
			func(m_instance, m_callback, nullptr);
		}
	}
	m_callback = other.m_callback;
	m_instance = other.m_instance;
	other.m_instance = VK_NULL_HANDLE;
	return *this;
}


AmrDebugCallback::AmrDebugCallback(VkInstance instance)
	:m_instance(instance)
{
#ifdef DEBUG_LAYER
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func == nullptr)
		throw std::runtime_error("failed to set up debug callback: extention vkCreateDebugReportCallbackEXT not found!");
	if (func(instance, &createInfo, nullptr, &m_callback) != VK_SUCCESS)
		throw std::runtime_error("failed to set up debug callback: cannot register callback!");
#endif
}

AmrDebugCallback::~AmrDebugCallback()
{
	if (m_instance != VK_NULL_HANDLE)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr)
		{
			func(m_instance, m_callback, nullptr);
		}
	}
}
