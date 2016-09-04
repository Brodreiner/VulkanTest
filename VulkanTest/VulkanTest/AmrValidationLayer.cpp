#pragma once

#include "AmrValidationLayer.hpp"

#ifdef DEBUG_LAYER

/**
Check if all validation layers from a (hardcoded) list are supported.
*/
bool AmrValidationLayer::isEveryLayerSupported()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : m_validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}

	}
	return true;
}

/**
Check if all validation layers from a (hardcoded) list are supported and throw an exception if not.
If validation layers are disabled do nothing.
*/
void AmrValidationLayer::checkLayerSupport()
{
	if (!isEveryLayerSupported())
	{
		throw std::runtime_error("validation layers requested, but not available!");
	}
}

/**
Return true if validation layers are enabled.
Return false if validation layers are disabled.
*/
bool AmrValidationLayer::isEnabled()
{
	return true;
}

/**
Return a vector of all validation layers.
If validation layers are disabled, return an empty vector.
*/
std::vector<const char*> AmrValidationLayer::getValidationLayers()
{
	std::vector<const char*> validationLayers;
	for (auto layer : m_validationLayers)
		validationLayers.push_back(layer);
	return validationLayers;
}

/**
Return the number of validation layers.
If validation layers are disabled, return 0.
*/
uint32_t AmrValidationLayer::size()
{
	return static_cast<uint32_t>(m_validationLayers.size());
}

/**
Return the pointer to the array of validation layers.
If validation layers are disabled, return nullptr.
*/
const char* const* AmrValidationLayer::data()
{
	return (!m_validationLayers.empty()) ? m_validationLayers.data() : nullptr;
}

#else

/**
Check if all validation layers from a (hardcoded) list are supported.
*/
bool AmrValidationLayer::isEveryLayerSupported()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : m_validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}

	}
	return true;
}

/**
Check if all validation layers from a (hardcoded) list are supported and throw an exception if not.
If validation layers are disabled do nothing.
*/
void AmrValidationLayer::checkLayerSupport()
{
}

/**
Return true if validation layers are enabled.
Return false if validation layers are disabled.
*/
bool AmrValidationLayer::isEnabled()
{
	return false;
}

/**
Return a vector of all validation layers.
If validation layers are disabled, return an empty vector.
*/
std::vector<const char*> AmrValidationLayer::getValidationLayers()
{
	return std::vector<const char*>();
}

/**
Return the number of validation layers.
If validation layers are disabled, return 0.
*/
uint32_t AmrValidationLayer::size()
{
	return 0;
}

/**
Return the pointer to the array of validation layers.
If validation layers are disabled, return nullptr.
*/
const char* const* AmrValidationLayer::data()
{
	return nullptr;
}

#endif