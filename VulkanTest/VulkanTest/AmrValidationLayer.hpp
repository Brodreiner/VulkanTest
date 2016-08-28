#pragma once


class AmrValidationLayer
{
	static constexpr bool m_isValidationLayerEnabled = true;
	static constexpr std::array<const char*, 1> m_validationLayers
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	/**
	Check if all validation layers from a (hardcoded) list are supported.
	*/
	static bool isEveryLayerSupported()
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

public:
	/**
	Check if all validation layers from a (hardcoded) list are supported and throw an exception if not.
	If validation layers are disabled do nothing.
	*/
	static void checkLayerSupport()
	{
		if (m_isValidationLayerEnabled && !isEveryLayerSupported())
		{
			throw std::runtime_error("validation layers requested, but not available!");
		}

	}

	/**
	Return true if validation layers are enabled.
	Return false if validation layers are disabled.
	*/
	static bool isEnabled()
	{
		return m_isValidationLayerEnabled;
	}

	/**
	Return a vector of all validation layers.
	If validation layers are disabled, return an empty vector.
	*/
	static std::vector<const char*> getValidationLayers()
	{
		std::vector<const char*> validationLayers;
		if (m_isValidationLayerEnabled)
		{
			for (auto layer : m_validationLayers)
				validationLayers.push_back(layer);
		}
		return validationLayers;
	}

	/**
	Return the number of validation layers.
	If validation layers are disabled, return 0.
	*/
	static uint32_t size()
	{
		return m_isValidationLayerEnabled ? static_cast<uint32_t>(m_validationLayers.size()) : 0;
	}

	/**
	Return the pointer to the array of validation layers.
	If validation layers are disabled, return nullptr.
	*/
	static const char* const* data()
	{
		return (m_isValidationLayerEnabled && !m_validationLayers.empty()) ? m_validationLayers.data() : nullptr;
	}

};
