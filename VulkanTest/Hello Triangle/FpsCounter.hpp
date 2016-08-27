#include <chrono>
#include <iostream>

class FpsCounter
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	unsigned frames = 0;
public:
	void reset()
	{
		start = std::chrono::high_resolution_clock::now();
		frames = 0;
	}
	void increment()
	{
		++frames;
	}
	bool isSecondOver()
	{
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		return(end - start >= std::chrono::seconds(1));
	}
	unsigned getFps()
	{
		return frames;
	}

	void autoPrint()
	{
		increment();
		if (isSecondOver())
		{
			std::cout << "FPS: " << getFps() << std::endl;
			reset();
		}
	}

};