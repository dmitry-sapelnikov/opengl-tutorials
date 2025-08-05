// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"

// Slightly yellowish light
const gltut::Vector3 DIR_LIGHT_POSITION = { 10.0f, 10.0f, 0.0f };
const gltut::Color DIR_LIGHT_COLOR = { 1.0f, 1.0f, 1.0f };

/// Creates boxes
void createBoxes(
	gltut::Engine& engine,
	gltut::PhongMaterialModel* phongMaterialModel)
{
	const int COUNT = 3;
	const float GEOMETRY_SIZE = 2.0f;
	const float STRIDE = 3.0f;
	auto* boxMesh = engine.getFactory()->getGeometry()->createSphere(
		GEOMETRY_SIZE * 0.5,
		8);

	GLTUT_CHECK(boxMesh, "Failed to create mesh");

	gltut::Rng rng;
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			const gltut::Vector3 position(
				(i - (COUNT - 1.0f) * 0.5f) * STRIDE,
				GEOMETRY_SIZE * 0.5f + rng.nextFloat(0.0, GEOMETRY_SIZE * 2.0f),
				(j - (COUNT - 1.0f) * 0.5f) * STRIDE);

			auto* object = engine.getScene()->createGeometry(
				boxMesh,
				phongMaterialModel->getMaterial(),
				gltut::Matrix4::transformMatrix(
					position,
					{ 0.0f, 0.0, 0.0f },
					rng.nextFloat(0.5f, 2.0f) * gltut::Vector3(1.0f, 1.0f, 1.0f)));

			GLTUT_CHECK(object, "Failed to create object");
		}
	}
}

/// Creates lights
gltut::GeometryNode* createLight(
	gltut::RenderPipeline& renderer,
	gltut::Scene& scene,
	gltut::ShaderMaterialBinding* lightShaderBinding,
	gltut::Mesh* lightMesh,
	const gltut::LightNode::Type lightType,
	const gltut::Vector3& position,
	const gltut::Color& color)
{
	auto* lightMaterial = renderer.createMaterial();
	GLTUT_CHECK(lightMaterial, "Failed to create light material");

	auto* materialPass = lightMaterial->createPass(0, lightShaderBinding, 0);

	materialPass->getShaderArguments()->setVec3("lightColor", color.r, color.g, color.b);
	GLTUT_CHECK(lightMesh, "Failed to create light mesh");

	auto* light = scene.createGeometry(lightMesh, lightMaterial);
	GLTUT_CHECK(light, "Failed to create light object");
	light->setTransform(gltut::Matrix4::translationMatrix(position));

	auto* lightSource = scene.createLight(lightType, gltut::Matrix4::identity(), light);
	lightSource->setAmbient(gltut::Color(color.r * 0.5f, color.g * 0.5f, color.b * 0.5f, 1.0f));
	lightSource->setDiffuse(color);
	lightSource->setSpecular(color);

	return light;
}

void createLights(
	gltut::Engine& engine,
	gltut::GeometryNode*& directionalLight)
{
	directionalLight = nullptr;

	gltut::Scene& scene = *engine.getScene();
	gltut::RenderPipeline& renderer = *engine.getRenderPipeline();

	auto* lightMesh = engine.getFactory()->getGeometry()->createSphere(0.2f, 10);
	GLTUT_CHECK(lightMesh, "Failed to create light mesh");

	auto* lightShader = renderer.getRenderer()->loadShader(
		"assets/light_shader.vs",
		"assets/light_shader.fs");
	GLTUT_CHECK(lightShader, "Failed to create light shader program");

	auto* materialBinding = renderer.createShaderMaterialBinding(lightShader);
	GLTUT_CHECK(materialBinding, "Failed to create light shader material binding");
	materialBinding->bind(
		gltut::ShaderMaterialBinding::Parameter::GEOMETRY_MATRIX,
		"model");

	auto* viewpointBinding = renderer.createShaderViewpointBinding(lightShader);
	GLTUT_CHECK(viewpointBinding, "Failed to create light shader viewpoint binding");
	viewpointBinding->bind(
		gltut::ShaderViewpointBinding::Parameter::VIEW_MATRIX,
		"view");

	viewpointBinding->bind(
		gltut::ShaderViewpointBinding::Parameter::PROJECTION_MATRIX,
		"projection");

	// Create a directional light]
	directionalLight = createLight(
		renderer,
		scene,
		materialBinding,
		lightMesh,
		gltut::LightNode::Type::DIRECTIONAL,
		DIR_LIGHT_POSITION,
		DIR_LIGHT_COLOR);

	GLTUT_CHECK(directionalLight, "Failed to create directional light");
	gltut::LightNode* directionalLightSource = dynamic_cast<gltut::LightNode*>(directionalLight->getChild(0));
	GLTUT_CHECK(directionalLightSource, "Failed to get directional light source");
	directionalLightSource->setTarget(-DIR_LIGHT_POSITION);
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

		auto* materialFactory = engine->getFactory()->getMaterial();

		auto* phongShader = materialFactory->createPhongShader(
			1, // 1 directional light
			0, // No point lights
			0); // No spot lights

		GLTUT_CHECK(phongShader, "Failed to create Phong shader");

		gltut::PhongMaterialModel* floorMaterialModel = materialFactory->createPhongMaterial(phongShader);
		GLTUT_CHECK(floorMaterialModel, "Failed to create Phong material model");
		floorMaterialModel->setDiffuse(renderer->createSolidColorTexture(0.5f, 0.5f, 0.5f, 1.0f));
		floorMaterialModel->setSpecular(renderer->createSolidColorTexture(0.0f, 0.0f, 0.0f, 1.0f));

		auto* floorGeometry = engine->getFactory()->getGeometry()->createBox(20.0f, 1.0f, 20.0f);
		GLTUT_CHECK(floorGeometry, "Failed to create floor geometry");
		scene->createGeometry(
			floorGeometry,
			floorMaterialModel->getMaterial(),
			gltut::Matrix4::translationMatrix({ 0.0f, -0.5f, 0.0f }));


		gltut::PhongMaterialModel* phongMaterialModel = materialFactory->createPhongMaterial(phongShader);
		GLTUT_CHECK(phongMaterialModel, "Failed to create Phong material model");

		gltut::Texture* diffuseTexture = renderer->createSolidColorTexture(1.0f, 0.5f, 0.31f, 1.0f);
		GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

		gltut::Texture* specularTexture = renderer->createSolidColorTexture(1.0f, 1.0f, 1.0f, 1.0f);
		GLTUT_CHECK(specularTexture, "Failed to create specular texture");

		phongMaterialModel->setDiffuse(diffuseTexture);
		phongMaterialModel->setSpecular(specularTexture);
		phongMaterialModel->setShininess(64.0f);

		createBoxes(*engine, phongMaterialModel);

		gltut::GeometryNode* directionalLight = nullptr;
		createLights(*engine, directionalLight);

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

			gltut::Matrix4 lightTransform =
				gltut::Matrix4::rotationMatrix({ 0.0f, time * 0.5f, 0.0f }) *
				gltut::Matrix4::translationMatrix(DIR_LIGHT_POSITION);

			directionalLight->setTransform(lightTransform);

			if (!engine->update())
			{
				break;
			}
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
