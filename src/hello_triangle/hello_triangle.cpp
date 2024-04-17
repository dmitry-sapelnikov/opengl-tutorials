// Includes
#include <iostream>
#include <string>
#include "engine/Engine.h"


///	The program entry point
int main()
{
	gltut::Engine* engine = gltut::createEngine(1024, 768);
	if (!engine)
	{
		return -1;
	}
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
	if (!scene->createMesh(
		gltut::VERTEX_FORMAT_POS3,
		vertices1,
		sizeof(vertices1) / sizeof(float),
		indices,
		sizeof(indices) / sizeof(unsigned)))
	{
		delete engine;
		return -1;
	}

	if (!scene->createMesh(
		gltut::VERTEX_FORMAT_POS3,
		vertices2,
		sizeof(vertices2) / sizeof(float),
		indices,
		sizeof(indices) / sizeof(unsigned)))
	{
		delete engine;
		return -1;
	}

	while (engine->update())
	{
	}

	delete engine;
	return 0;
}
