#include "AmrEngine.hpp"

int main()
{
	AmrEngine* amrEngine = new AmrEngine(800, 600, "Amr Engine");
	delete amrEngine;
	return 0;
}
