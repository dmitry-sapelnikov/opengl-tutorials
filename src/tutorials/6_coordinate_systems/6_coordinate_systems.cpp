// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"

static const size_t BOX_COUNT = 100;
static const float POSITION_RANGE = 5.0f;

///	The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Coordinate Systems");
		engine->getWindow()->showFPS(true);

		auto* device = engine->getDevice();
		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createBox(1.0f, 1.0f, 1.0f);

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

		gltut::Shader* shader = device->getShaders()->load(
			"assets/shader.vs",
			"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program");
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);

		auto* renderPipeline = engine->getRenderer();
		auto* shaderBinding = renderPipeline->createShaderMaterialBinding(shader);
		GLTUT_CHECK(shaderBinding != nullptr, "Failed to create shader binding");
		shaderBinding->bind(gltut::ShaderMaterialBinding::Parameter::GEOMETRY_MATRIX, "model");

		gltut::Texture* texture1 = device->getTextures()->load("assets/container.jpg", {});
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture");

		gltut::Texture* texture2 = device->getTextures()->load("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture");

		auto* material = renderPipeline->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		auto* materialPass = material->createPass(0, shaderBinding, 2);
		GLTUT_CHECK(materialPass != nullptr, "Failed to create material pass");

		materialPass->getTextures()->setTexture(texture1, 0);
		materialPass->getTextures()->setTexture(texture2, 1);

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> boxes;
		std::vector<gltut::Vector3> boxPositions;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			boxes.push_back(scene->createGeometry(geometry, material));
			boxPositions.emplace_back(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));
		}

		gltut::Matrix4 view = gltut::Matrix4::translationMatrix({ 0.0f, 0.0f, -20.0f });
		shader->setMat4("view", view.data());

		auto start = std::chrono::high_resolution_clock::now();
		while (engine->update())
		{
			const gltut::Point2u size = engine->getWindow()->getSize();
			GLTUT_CHECK(size.y != 0, "Invalid window size");

			const gltut::Matrix4 projection = gltut::Matrix4::perspectiveProjectionMatrix(
				45.0f,
				static_cast<float>(size.x) / static_cast<float>(size.y),
				0.1f,
				100.0f);
			shader->setMat4("projection", projection.data());

			auto now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float>(now - start).count();
			auto rotation = gltut::Matrix4::rotationMatrix({ time, time, time });

			for (size_t i = 0; i < BOX_COUNT; ++i)
			{
				boxes[i]->setTransform(
					gltut::Matrix4::translationMatrix(boxPositions[i]) * rotation);
			}
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
