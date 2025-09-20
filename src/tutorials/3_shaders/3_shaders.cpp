// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "engine/Engine.h"
#include "engine/core/Check.h"
#include <array>
#include <chrono>
#include <iostream>
#include <string>

namespace
{
// Local constants
/// Vertex shader source code
const char* VERTEX_SHADER = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 ourColor;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
})";

// Fragment shader source code
const char* FRAGMENT_SHADER = R"(
#version 330 core
in vec4 ourColor;
out vec4 FragColor;
uniform float colorScale;
void main()
{
	FragColor = colorScale * ourColor;
})";

// End of the anonymous namespace
}

/// The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");

		engine->getWindow()->setTitle("Shaders");
		engine->getWindow()->showFPS(true);

		float vertices[] = {
			// positions         // colors
			0.5f,
			-0.5f,
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			1.0f, // bottom right
			-0.5f,
			-0.5f,
			0.0f,
			0.0f,
			1.0f,
			0.0f,
			1.0f, // bottom left
			0.0f,
			0.5f,
			0.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f // top
		};

		std::array<unsigned, 3> indices = {
			// note that we start from 0!
			0,
			1,
			2, // first Triangle
		};

		auto* device = engine->getDevice();
		auto* scene = engine->getScene();

		gltut::Shader* shader = device->getShaders()->create(
			VERTEX_SHADER,
			FRAGMENT_SHADER);

		GLTUT_CHECK(shader != 0, "Failed to create shader program")

		auto* geometry = device->getGeometries()->create(
			gltut::VERTEX_FORMAT_POS3_COLOR4,
			3,
			vertices,
			3,
			indices.data());

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

		auto* renderer = engine->getRenderer();
		auto* binding = renderer->createShaderBinding(shader);
		GLTUT_CHECK(binding != nullptr, "Failed to create shader binding");

		auto* material = renderer->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		auto* pass = material->createPass(0, binding, 0, 0);
		GLTUT_CHECK(pass != nullptr, "Failed to create material pass");
		// Since our geometry does not have normals, disable face culling
		pass->setFaceCulling(gltut::FaceCullingMode::NONE);

		scene->createGeometry(geometry, material);
		auto start = std::chrono::high_resolution_clock::now();
		while (engine->update())
		{
			auto now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float>(now - start).count();
			float colorScale = (std::sin(time) * 0.5f) + 0.5f;
			shader->setFloat("colorScale", colorScale);
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
