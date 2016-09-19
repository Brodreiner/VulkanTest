#pragma once

#include <vulkan/vulkan.h>

#include <functional>

struct GLFWwindow;

class AmrWindow
{
	GLFWwindow* m_window = nullptr;
	std::function<void(int, int)> m_resizeCallback = defaultResizeCallback;
	std::function<void()> m_eventLoopCallback = []() {};

	static void onWindowResized(GLFWwindow* window, int width, int height);

	static void defaultResizeCallback(int width, int height);

public:
	AmrWindow() = default;
	AmrWindow(const AmrWindow&) = delete;
	AmrWindow(AmrWindow&&) = delete;
	AmrWindow& operator=(const AmrWindow&) = delete;
	AmrWindow& operator=(AmrWindow&& other);
	~AmrWindow() = default;

	AmrWindow(uint32_t width, uint32_t height, const std::string& title);

	void mainLoop();

	void setResizeCallback(std::function<void(int, int)> callback);

	void setEventLoopCallback(std::function<void()> callback);

	operator GLFWwindow*() const;
};