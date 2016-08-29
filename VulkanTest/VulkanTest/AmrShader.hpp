#pragma once

class AmrShader
{
	VkShaderModule m_shader;
	VkDevice m_device;

	static std::vector<char> readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open())
			throw std::runtime_error("failed to open file " + filename + "!");
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		return buffer;
	}

	void createShader(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = (uint32_t*)code.data();

		if (vkCreateShaderModule(m_device, &createInfo, nullptr, &m_shader) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module!");
	}

public:

	AmrShader(VkDevice device, const std::string& filename)
		: m_device(device)
	{
		std::vector<char> code = readFile(filename);
		createShader(code);
	}

	~AmrShader()
	{
		vkDestroyShaderModule(m_device, m_shader, nullptr);
	}

	operator VkShaderModule() const
	{
		return m_shader;
	}

};
