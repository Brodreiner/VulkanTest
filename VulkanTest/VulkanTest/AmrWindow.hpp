#pragma once

class AmrWindow
{
	GLFWwindow* m_window;
	std::function<void(int, int)> m_resizeCallback = defaultResizeCallback;
	std::function<void()> m_eventLoopCallback = []() {};

	static void onWindowResized(GLFWwindow* window, int width, int height)
	{
		AmrWindow* app = reinterpret_cast<AmrWindow*>(glfwGetWindowUserPointer(window));
		app->m_resizeCallback(width, height);
	}

	static void defaultResizeCallback(int width, int height)
	{
		std::cout << "Window resized: " << width << "x" << height << std::endl;
	}

public:
	AmrWindow(uint32_t width, uint32_t height, const std::string& title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, AmrWindow::onWindowResized);
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
		}
	}
	void setResizeCallback(std::function<void(int, int)> callback)
	{
		m_resizeCallback = callback;
	}
	void setEventLoopCallback(std::function<void()> callback)
	{
		m_eventLoopCallback = callback;
	}

	operator GLFWwindow*() const
	{
		return m_window;
	}
};