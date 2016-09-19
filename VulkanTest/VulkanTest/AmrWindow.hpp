#pragma once

#include <vulkan/vulkan.h>

#include <functional>

struct GLFWwindow;

class AmrWindow
{
	GLFWwindow* m_window = nullptr;
	std::function<void(int, int)> m_resizeCallback = defaultResizeCallback;
	std::function<void()> m_eventLoopCallback = []() {};
	std::function<void(int, int, int, int)> m_keyCallback = [](int, int, int, int) {};
	std::function<void(double, double)> m_mouseMoveCallback = [](double, double) {};
	std::function<void(int, int, int)> m_mouseClickCallback = [](int, int, int) {};

	static void onWindowResized(GLFWwindow* window, int width, int height);
	static void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
	static void defaultResizeCallback(int width, int height);
	static void onMouseClick(GLFWwindow* window, int button, int action, int mods);

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
	void setKeyCallback(std::function<void(int, int, int, int)> callback);
	void setMouseMoveCallback(std::function<void(double, double)> callback);
	void setMouseClickCallback(std::function<void(int, int, int)> callback);

	void disableCursor();
	void enableCursor();

	operator GLFWwindow*() const;
};