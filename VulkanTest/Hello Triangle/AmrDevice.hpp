#pragma once


class AmrDevice
{
	VkDevice m_device;


	~AmrDevice()
	{
		vkDestroyDevice(m_device, nullptr);
	}
};