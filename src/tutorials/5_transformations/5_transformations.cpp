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

		engine->getWindow()->setTitle("Transformations");
		engine->getWindow()->showFPS(true);

		float vertices[] = {
			// positions       // texture coords
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
		};

		gltut::u32 indices[] = {
			 0, 1, 3, // first triangle
			 1, 2, 3  // second triangle
		};

		auto* scene = engine->getScene();
		auto* mesh = scene->createMesh(
			gltut::VERTEX_FORMAT_POS3_TEX2,
			4,
			vertices,
			6,
			indices);

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh")

		gltut::Shader* shader = engine->getRenderer()->loadShader(
			"assets/shader.vs",
			"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);
		shader->setSceneParameterName(gltut::Shader::SceneParameter::MODEL, "model");

		gltut::Texture* texture1 = engine->getRenderer()->loadTexture("assets/container.jpg");
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture")

		gltut::Texture* texture2 = engine->getRenderer()->loadTexture("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture")

		auto* material = scene->createMaterial(shader);
		GLTUT_CHECK(material != nullptr, "Failed to create material")
		material->setTexture(texture1, 0);
		material->setTexture(texture2, 1);
		
		auto* object = scene->createObject(mesh, material);

		auto start = std::chrono::high_resolution_clock::now();
		while (engine->update())
		{
			auto now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float>(now - start).count();
			object->setTransform(
				gltut::Matrix4::rotationMatrix({ 0.0f, 0.0f, time }) *
				gltut::Matrix4::translationMatrix({ 0.5f, 0.f, 0.f }) *
				gltut::Matrix4::scaleMatrix({ 0.5f, 0.5f, 0.5 }));
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
