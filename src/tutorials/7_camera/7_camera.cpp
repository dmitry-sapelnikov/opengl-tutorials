// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include "engine/core/Check.h"
#include "engine/Engine.h"
#include "engine/MeshCreation.h"
#include "engine/Math/Rng.h"
#include "engine/scene/camera/MouseCameraController.h"

static const size_t BOX_COUNT = 100;
static const float POSITION_RANGE = 5.0f;

///	The program entry point
int main()
{
	gltut::Engine* engine = nullptr;
	try
	{
		engine = gltut::createEngine(1024, 768);
		GLTUT_CHECK(engine != nullptr, "Failed to create engine")

			engine->getWindow()->setTitle("Camera");
		engine->getWindow()->showFPS(true);

		auto* scene = engine->getScene();
		auto* mesh = gltut::createBoxMesh(*scene, 1.0f, 1.0f, 1.0f);

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh")

			gltut::Shader* shader = engine->getRenderer()->loadShader(
				"assets/shader.vs",
				"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);
		shader->setModelMatrixName("model");
		shader->setProjectionMatrixName("projection");
		shader->setViewMatrixName("view");

		gltut::Texture* texture1 = engine->getRenderer()->loadTexture("assets/container.jpg");
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture")

		gltut::Texture* texture2 = engine->getRenderer()->loadTexture("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture")

		auto* material = scene->createMaterial(shader);
		GLTUT_CHECK(material != nullptr, "Failed to create material")
		material->setTexture(texture1, 0);
		material->setTexture(texture2, 1);

		gltut::Rng rng;
		std::vector<gltut::SceneObject*> boxes;
		std::vector<gltut::Vector3> boxPositions;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			boxes.push_back(scene->createObject(mesh, material));
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
