// Includes
#include "engine/IEngine.h"

int main()
{
	gltut::IEngine* engine = gltut::createEngine();
	if (!engine)
	{
		return -1;
	}

	gltut::IWindow* window = engine->createWindow(1024, 768, "Hello Window");

	if (!window)
	{
		delete engine;
		return -1;
	}

	window->showFPS(true);
	while (engine->doStep())
	{
		// Do nothing
	}
	delete engine;
	return 0;
}
