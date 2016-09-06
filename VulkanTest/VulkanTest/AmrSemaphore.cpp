#pragma once

#include "AmrSemaphore.hpp"
#include <stdexcept>

AmrSemaphore::AmrSemaphore(VkDevice device)
	: m_device(device)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_semaphore) != VK_SUCCESS)
		throw std::runtime_error("failed to create semaphore!");
}

AmrSemaphore::~AmrSemaphore()
{
	if (m_semaphore != VK_NULL_HANDLE)
		vkDestroySemaphore(m_device, m_semaphore, nullptr);
}

AmrSemaphore::operator VkSemaphore() const
{
	return m_semaphore;
}

