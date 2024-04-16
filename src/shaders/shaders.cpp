// Includes
#include <iostream>
#include <string>
#include "engine/core/Check.h"
#include "engine/Engine.h"

///	The program entry point
int main()
{
	gltut::Engine* engine = nullptr;

	try
	{
		gltut::Engine* engine = gltut::createEngine(1024, 768);
		GLTUT_CHECK(engine != nullptr, "Failed to create engine")

		engine->getWindow()->setTitle("Shaders");
		engine->getWindow()->showFPS(true);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned indices[] = {  // note that we start from 0!
			0, 1, 2,  // first Triangle
		};

		auto* scene = engine->getScene();
		auto* mesh = scene->createMesh(
			vertices,
			sizeof(vertices) / sizeof(float),
			indices,
			sizeof(indices) / sizeof(unsigned));

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh")

		unsigned shader = engine->getRenderer()->createShaderProgram(
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"out vec4 vertexColor;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(aPos, 1.0);\n"
			"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
			"}",

			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 vertexColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vertexColor;\n"
			"}");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		mesh->setShaderProgram(shader);

		while (engine->update())
		{
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An exception occurred: " << e.what() << std::endl;
		delete engine;
		return -1;
	}

	delete engine;
	return 0;
}
