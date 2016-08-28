#pragma once

class AmrEngine
{
	AmrWindow m_amrWindow;
	AmrInstance m_amrInstance;
	AmrDebugCallback m_amrDebugCallback;
	AmrSurface m_amrSurface;
	AmrPhysicalDevice m_amrPhysicalDevice;
	AmrQueueFamily m_amrQueueFamily;
	AmrDevice m_amrDevice;
	AmrQueue m_amrGraphicsQueue;
	AmrQueue m_amrPresentQueue;
	AmrSwapChain m_amrSwapChain;
public:
	AmrEngine(uint32_t width, uint32_t height, const std::string& title)
		: m_amrWindow(width, height, title)
		, m_amrDebugCallback(m_amrInstance)
		, m_amrSurface(m_amrWindow, m_amrInstance)
		, m_amrPhysicalDevice(m_amrInstance, m_amrSurface)
		, m_amrQueueFamily(m_amrPhysicalDevice, m_amrSurface)
		, m_amrDevice(m_amrPhysicalDevice, m_amrQueueFamily.getDeviceQueueCreateInfoSize(), m_amrQueueFamily.getDeviceQueueCreateInfoData())
		, m_amrGraphicsQueue(m_amrDevice, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), 0)
		, m_amrPresentQueue(m_amrDevice, m_amrQueueFamily.getPresentQueueFamilyIndex(), 0)
		, m_amrSwapChain(m_amrPhysicalDevice, m_amrDevice, m_amrSurface, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), m_amrQueueFamily.getPresentQueueFamilyIndex(), {width, height})

	{
		m_amrWindow.mainLoop();
	}

};