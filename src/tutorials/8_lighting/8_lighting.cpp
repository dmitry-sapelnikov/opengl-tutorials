// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include "engine/core/Check.h"
#include "engine/Engine.h"
#include "engine/MeshCreation.h"

namespace
{
	const gltut::Vector3 LIGHT_POSITION = { 2.0, 3.0f, 5.0f };
}

///	The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine, "Failed to create engine");

		engine->getWindow()->setTitle("Lighting");
		engine->getWindow()->showFPS(true);

		auto* scene = engine->getScene();
		auto* mesh = gltut::createSphereMesh(*scene, 1.0f, 10);//gltut::createBoxMesh(*scene, 1.0f, 1.0f, 1.0f);
		GLTUT_CHECK(mesh, "Failed to create mesh");

		gltut::Shader* phongShader = engine->getRenderer()->loadShader(
			"assets/phong_shader.vs",
			"assets/phong_shader.fs");
		GLTUT_CHECK(phongShader, "Failed to create phong shader program");

		phongShader->setVec3("lightPos", LIGHT_POSITION.x, LIGHT_POSITION.y, LIGHT_POSITION.z);
		phongShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		phongShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		phongShader->setModelMatrixName("model");
		phongShader->setProjectionMatrixName("projection");
		phongShader->setViewMatrixName("view");
		phongShader->setNormalMatrixName("normalMat");

		auto* phongMaterial = scene->createMaterial(phongShader);
		GLTUT_CHECK(phongMaterial, "Failed to create phong material");

		auto* object = scene->createObject(mesh, phongMaterial);
		GLTUT_CHECK(object, "Failed to create object");

		auto* lightShader = engine->getRenderer()->loadShader(
			"assets/light_shader.vs",
			"assets/light_shader.fs");
		GLTUT_CHECK(lightShader, "Failed to create light shader program");

		lightShader->setModelMatrixName("model");
		lightShader->setProjectionMatrixName("projection");
		lightShader->setViewMatrixName("view");

		auto* lightMaterial = scene->createMaterial(lightShader);
		GLTUT_CHECK(lightMaterial, "Failed to create light material");

		auto* light = scene->createObject(mesh, lightMaterial);
		light->setTransform(gltut::Matrix4::transformMatrix(
			LIGHT_POSITION,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.2f, 0.2f, 0.2f }));
		GLTUT_CHECK(light, "Failed to create light object");

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ -2.0f, 2.0f, 6.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			150.0f);
		GLTUT_CHECK(camera, "Failed to create camera");

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		const auto startTime = std::chrono::high_resolution_clock::now();
		while (true)
		{
			const auto now = std::chrono::high_resolution_clock::now();
			const float time = std::chrono::duration<float>(now - startTime).count();

			const gltut::Vector3 rotation = {time, 0.0f, 0.0f};
			object->setTransform(gltut::Matrix4::transformMatrix(
				{ 0.0f, 0.0f, 0.0f },
				rotation,
				{ 1.0f, 2.0f, 1.0f }));

			if (!engine->update())
			{
				break;
			}
		}
	}
	GLTUT_APPLICATION_CATCH

	return 0;
}
