#pragma once

#include <chrono>

class GameTime
{
	std::chrono::high_resolution_clock::time_point m_lastTime = std::chrono::high_resolution_clock::now();
public:
	float getTimeSinceLastCall()
	{
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		float timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - m_lastTime).count() / 1000000000.0f;
		m_lastTime = currentTime;
		return timeDelta;
	}
};

