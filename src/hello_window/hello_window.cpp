// Includes
#include "engine/Engine.h"

int main()
{
	gltut::Engine* engine = gltut::createEngine();
	if (!engine)
	{
		return -1;
	}

	gltut::Window* window = engine->createWindow(1024, 768, "Hello WindowC");

	if (!window)
	{
		delete engine;
		return -1;
	}

	window->showFPS(true);
	while (engine->update())
	{
		// Do nothing
	}
	delete engine;
	return 0;
}
