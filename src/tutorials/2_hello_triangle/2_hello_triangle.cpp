// Includes
#include <iostream>
#include <string>
#include "engine/Engine.h"

///	The program entry point
int main()
{
	gltut::Engine* engine = nullptr;
	try
	{
		engine = gltut::createEngine(1024, 768);
		GLTUT_CHECK(engine != nullptr, "Failed to create engine")
	
		engine->getWindow()->setTitle("Hello Triangle");
		engine->getWindow()->showFPS(true);

		float vertices1[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		float vertices2[] = {
			1.0f,  1.0f, 0.0f,  // top right
			1.0f, 0.25f, 0.0f,  // bottom right
			0.25f, 0.25f, 0.0f,  // bottom left
			0.25f, 1.0f, 0.0f   // top left 
		};

		unsigned indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		auto* scene = engine->getScene();
		auto* mesh1 = scene->createMesh(
			gltut::VERTEX_FORMAT_POS3,
			vertices1,
			sizeof(vertices1) / sizeof(float),
			indices,
			sizeof(indices) / sizeof(unsigned));

		GLTUT_CHECK(mesh1 != nullptr, "Failed to create mesh #1")

		auto* mesh2 = scene->createMesh(
			gltut::VERTEX_FORMAT_POS3,
			vertices2,
			sizeof(vertices2) / sizeof(float),
			indices,
			sizeof(indices) / sizeof(unsigned));

		GLTUT_CHECK(mesh2 != nullptr, "Failed to create mesh #2")

		while (engine->update())
		{
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An ERROR occurred: " << e.what() << std::endl;
		// Wait for the user to close the console window
		std::cin.get();
		delete engine;
		return -1;
	}
	delete engine;
	return 0;
}
