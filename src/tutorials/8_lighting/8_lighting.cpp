// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/scene/material/PhongMaterial.h"
#include "engine/Engine.h"

namespace
{
const gltut::Vector3 LIGHT_POSITION = { 0.0, 10.0f, 20.0f };
const gltut::Vector3 LIGHT_COLOR = { 1.0, 1.0f, 1.0f };
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

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* mesh = engine->getGeometryFactory()->createSphere(1.0f, 10);
		GLTUT_CHECK(mesh, "Failed to create mesh");

		gltut::SceneShaderBinding* phongShader = gltut::createPhongShader(*renderer, *scene);
		GLTUT_CHECK(phongShader, "Failed to create Phong shader");

		phongShader->getShader()->setVec3("lightPos", LIGHT_POSITION.x, LIGHT_POSITION.y, LIGHT_POSITION.z);
		phongShader->getShader()->setVec3("lightColor", LIGHT_COLOR.x, LIGHT_COLOR.y, LIGHT_COLOR.z);

		gltut::Texture* ambientTexture = renderer->createSolidColorTexture(0.1f, 0.1f, 0.1f);
		GLTUT_CHECK(ambientTexture, "Failed to create ambient texture");

		gltut::Texture* diffuseTexture = renderer->loadTexture("assets/container2.png");
		GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

		gltut::Texture* specularTexture = renderer->loadTexture("assets/container2_specular.png");
		GLTUT_CHECK(specularTexture, "Failed to create specular texture");

		auto* phongMaterial = scene->createMaterial(phongShader);
		GLTUT_CHECK(phongMaterial, "Failed to create Phong material");

		gltut::setPhongMaterialParameters(
			*phongMaterial,
			ambientTexture,
			diffuseTexture,
			specularTexture);

		auto* object = scene->createGeometry(mesh, phongMaterial);
		GLTUT_CHECK(object, "Failed to create object");

		auto* lightShader = renderer->loadShader(
			"assets/light_shader.vs",
			"assets/light_shader.fs");
		GLTUT_CHECK(lightShader, "Failed to create light shader program");

		auto* lightShaderBinding = scene->createShaderBinding(lightShader);
		GLTUT_CHECK(lightShaderBinding, "Failed to create light shader binding");

		gltut::bindModelViewProjectionShaderParameters(lightShaderBinding, "model", "view", "projection");
		auto* lightMaterial = scene->createMaterial(lightShaderBinding);
		GLTUT_CHECK(lightMaterial, "Failed to create light material");

		auto* light = scene->createGeometry(mesh, lightMaterial);
		GLTUT_CHECK(light, "Failed to create light object");
		light->setTransform(gltut::Matrix4::transformMatrix(
			LIGHT_POSITION,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.2f, 0.2f, 0.2f }));

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

			const gltut::Vector3 rotation = { 0.0f, time, 0.0f };
			object->setTransform(gltut::Matrix4::transformMatrix(
				{ 0.0f, 0.0f, 0.0f },
				rotation,
				{ 2.0f, 2.0f, 2.0f }));
			if (!engine->update())
			{
				break;
			}
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
