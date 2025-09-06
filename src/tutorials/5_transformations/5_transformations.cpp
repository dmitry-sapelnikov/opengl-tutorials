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
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");

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

		auto* device = engine->getDevice();
		auto* scene = engine->getScene();
		auto* geometry = device->getGeometries()->create(
			gltut::VERTEX_FORMAT_POS3_TEX2,
			4,
			vertices,
			6,
			indices);

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

		gltut::Shader* shader = device->getShaders()->load(
			"assets/shader.vs",
			"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program");
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);

		auto* renderer = engine->getRenderer();
		auto* binding = renderer->createShaderBinding(shader);
		GLTUT_CHECK(binding != nullptr, "Failed to create shader binding");

		binding->bind(gltut::ShaderRendererBinding::Parameter::GEOMETRY_MATRIX, "model");

		gltut::Texture* texture1 = device->getTextures()->load("assets/container.jpg", {});
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture")

			gltut::Texture* texture2 = device->getTextures()->load("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture")

		auto* material = renderer->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");
		auto* materialPass = material->createPass(0, binding, 2);
		GLTUT_CHECK(materialPass != nullptr, "Failed to create material pass");

		materialPass->getTextures()->setTexture(texture1, 0);
		materialPass->getTextures()->setTexture(texture2, 1);
		materialPass->setFaceCulling(gltut::FaceCullingMode::NONE);

		auto* object = scene->createGeometry(geometry, material);

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
	GLTUT_APPLICATION_CATCH;
	return 0;
}
