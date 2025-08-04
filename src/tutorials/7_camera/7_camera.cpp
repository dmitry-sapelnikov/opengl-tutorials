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

		engine->getWindow()->setTitle("Camera");
		engine->getWindow()->showFPS(true);

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* mesh = engine->getFactory()->getGeometry()->createBox(1.0f, 1.0f, 1.0f);

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh")

		gltut::Shader* shader = renderer->loadShader(
			"assets/shader.vs",
			"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);

		auto* shaderBinding = scene->createShaderBinding(shader);
		GLTUT_CHECK(shaderBinding != nullptr, "Failed to create shader binding")

		gltut::bindModelViewProjectionShaderParameters(
			shaderBinding,
			"model",
			"view",
			"projection");

		gltut::Texture* texture1 = renderer->loadTexture("assets/container.jpg");
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture");

		gltut::Texture* texture2 = renderer->loadTexture("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture");

		auto* material = scene->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		auto* materialPass = material->createPass(0, shaderBinding, 2);
		GLTUT_CHECK(materialPass != nullptr, "Failed to create material pass");

		materialPass->setTexture(texture1, 0);
		materialPass->setTexture(texture2, 1);

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> boxes;
		std::vector<gltut::Vector3> boxPositions;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			boxes.push_back(scene->createGeometry(mesh, material));
			boxPositions.emplace_back(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));
		}

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ 0.0f, 0.0f, 20.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			100.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		auto start = std::chrono::high_resolution_clock::now();
		while (engine->update())
		{
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
