// Includes
#include <memory>
#include "engine/Engine.h"

int main()
{
	std::unique_ptr<gltut::Engine> engine(
		gltut::createEngine(1024, 768));

	if (engine == nullptr)
	{
		std::cerr << "Failed to create engine" << std::endl;
		return -1;
	}
	
	auto* window = engine->getWindow();
	window->setTitle("Hello Window");
	window->showFPS(true);

	while (engine->update())
	{
	}
	return 0;
}
