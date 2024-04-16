// Includes
#include "engine/Engine.h"

int main()
{
	gltut::Engine* engine = gltut::createEngine(1024, 768);
	if (!engine)
	{
		return -1;
	}
	engine->getWindow()->setTitle("Hello Window");
	engine->getWindow()->showFPS(true);

	while (engine->update())
	{
		// Do nothing
	}
	delete engine;
	return 0;
}
