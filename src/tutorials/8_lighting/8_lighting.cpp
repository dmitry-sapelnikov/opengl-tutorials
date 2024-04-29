// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include "engine/core/Check.h"
#include "engine/Engine.h"
#include "engine/MeshCreation.h"

///	The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine.get() != nullptr, "Failed to create engine");

		engine->getWindow()->setTitle("Lighting");
		engine->getWindow()->showFPS(true);

		auto* scene = engine->getScene();
		auto* mesh = gltut::createBoxMesh(*scene, 1.0f, 1.0f, 1.0f);

		GLTUT_CHECK(mesh != nullptr, "Failed to create mesh");

		gltut::Shader* boxShader = engine->getRenderer()->loadShader(
			"assets/shader.vs",
			"assets/box_shader.fs");

		GLTUT_CHECK(boxShader != 0, "Failed to create box shader program");
		boxShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		boxShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);

		boxShader->setModelMatrixName("model");
		boxShader->setProjectionMatrixName("projection");
		boxShader->setViewMatrixName("view");

		auto* boxMaterial = scene->createMaterial(boxShader);
		GLTUT_CHECK(boxMaterial != nullptr, "Failed to create box material");

		auto* box = scene->createObject(mesh, boxMaterial);
		box->setTransform(gltut::Matrix4::identity());

		auto* lightShader = engine->getRenderer()->loadShader(
			"assets/shader.vs",
			"assets/light_shader.fs");
		GLTUT_CHECK(lightShader != nullptr, "Failed to create light shader program");

		lightShader->setModelMatrixName("model");
		lightShader->setProjectionMatrixName("projection");
		lightShader->setViewMatrixName("view");

		auto* lightMaterial = scene->createMaterial(lightShader);
		GLTUT_CHECK(lightMaterial != nullptr, "Failed to create light material");
		auto* light = scene->createObject(mesh, lightMaterial);
		light->setTransform(
			gltut::Matrix4::translationMatrix({ 1.2f, 1.0f, 2.0f }) *
			gltut::Matrix4::scaleMatrix({ 0.2f, 0.2f, 0.2f }));

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ -2.0f, 2.0f, 6.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			100.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		while (engine->update())
		{
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An ERROR occurred: " << e.what() << std::endl;
		// Wait for the user to close the console window
		std::cin.get();
		return -1;
	}
	return 0;
}
