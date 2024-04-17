// Includes
#include <array>
#include <chrono>
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
		engine = gltut::createEngine(1024, 768);
		GLTUT_CHECK(engine != nullptr, "Failed to create engine")

		engine->getWindow()->setTitle("Shaders");
		engine->getWindow()->showFPS(true);

		float vertices[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f   // top 
		};

		std::array<unsigned, 3> indices = {  // note that we start from 0!
			0, 1, 2,  // first Triangle
		};

		auto* scene = engine->getScene();
		auto* mesh = scene->createMesh(
			gltut::VERTEX_FORMAT_POS3_COLOR4,
			vertices,
			gltut::int32(sizeof(vertices) / sizeof(float)),
			indices.data(),
			gltut::int32(indices.size()));

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh")

		gltut::Shader* shader = engine->getRenderer()->createShader(
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec4 aColor;\n"
			"out vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(aPos, 1.0);\n"
			"	ourColor = aColor;\n"
			"}",

			"#version 330 core\n"
			"in vec4 ourColor;\n"
			"out vec4 FragColor;\n"
			"uniform float colorScale;"
			"void main()\n"
			"{\n"
			"	FragColor = colorScale * ourColor;\n"
			"}");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		mesh->setShader(shader);

		for (;;)
		{
			float time = std::chrono::duration<float>(
				std::chrono::steady_clock::now().time_since_epoch()).count();

			float colorScale = (std::sin(time) / 2.0f) + 0.5f;
			shader->use();
			shader->setFloat("colorScale", colorScale);

			if (!engine->update())
			{
				break;
			}
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
