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
	AmrShader() = default;
	AmrShader(const AmrShader&) = delete;
	AmrShader(AmrShader&&) = delete;
	AmrShader& operator=(const AmrShader&) = delete;
	AmrShader& operator=(AmrShader&& other);
	~AmrShader();

	AmrShader(VkDevice device, const std::string& filename);


	operator VkShaderModule() const;

};
