#pragma once

#include <vulkan/vulkan.h>
#include <array>
#include <vector>

class AmrValidationLayer
{
	static constexpr std::array<const char*, 1> m_validationLayers
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	/**
	Check if all validation layers from a (hardcoded) list are supported.
	*/
	static bool isEveryLayerSupported();

public:
	AmrValidationLayer() = delete;
	AmrValidationLayer(const AmrValidationLayer&) = delete;
	AmrValidationLayer(AmrValidationLayer&&) = delete;
	AmrValidationLayer& operator=(const AmrValidationLayer&) = delete;
	AmrValidationLayer& operator=(AmrValidationLayer&& other) = delete;
	~AmrValidationLayer() = delete;

	/**
	Check if all validation layers from a (hardcoded) list are supported and throw an exception if not.
	If validation layers are disabled do nothing.
	*/
	static void checkLayerSupport();

	/**
	Return true if validation layers are enabled.
	Return false if validation layers are disabled.
	*/
	static bool isEnabled();

	/**
	Return a vector of all validation layers.
	If validation layers are disabled, return an empty vector.
	*/
	static std::vector<const char*> getValidationLayers();

	/**
	Return the number of validation layers.
	If validation layers are disabled, return 0.
	*/
	static uint32_t size();

	/**
	Return the pointer to the array of validation layers.
	If validation layers are disabled, return nullptr.
	*/
	static const char* const* data();

};
