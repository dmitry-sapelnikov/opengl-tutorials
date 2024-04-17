// Includes
#include "engine/Engine.h"

int main()
{
	gltut::Engine* engine = gltut::createEngine(1024, 768);
	if (!engine)
	{
		return -1;
	}
	
	auto* window = engine->getWindow();
	window->setTitle("Hello Window");
	window->showFPS(true);

	while (engine->update())
	{
	}
	delete engine;
	return 0;
}
