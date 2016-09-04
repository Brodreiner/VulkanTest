#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class AmrShader
{
	VkShaderModule m_shader;
	VkDevice m_device;

	static std::vector<char> readFile(const std::string& filename);

	void createShader(const std::vector<char>& code);

public:

	AmrShader(VkDevice device, const std::string& filename);

	~AmrShader();

	operator VkShaderModule() const;

};
