#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrShader
{
	VkShaderModule m_shader = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

	static std::vector<char> readFile(const std::string& filename);

	void createShader(const std::vector<char>& code);

public:

	AmrShader(VkDevice device, const std::string& filename);

	~AmrShader();

	operator VkShaderModule() const;

};
