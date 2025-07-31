// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/Engine.h"

const std::vector<gltut::Vector3> POINT_LIGHT_POSITIONS = {
	{0.0, 10.0f, 20.0f},
	{5.0, 0.0f, 0.0f},
	{0.0, 5.0f, 0.0f}
};

const std::vector<gltut::Color> POINT_LIGHT_COLORS = {
	{1.0f, 1.0f, 1.0f}, // White light
	{1.0f, 0.5f, 0.5f}, // Red light
	{0.5f, 0.5f, 1.0f}  // Blue light
};

const std::vector<gltut::Vector3> POINT_LIGHT_ROTATIONS = {
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, -0.5f},
	{1.5f, 0.0f, 0.0f},
};

const gltut::Color SPOT_LIGHT_COLOR = { 1.0f, 1.0f, 1.0f }; // White light
constexpr float SPOT_LIGHT_Y = 10.0f;
constexpr float SPOT_LIGHT_Z = 6.0f;

/// Creates boxes
void createBoxes(
	gltut::Engine& engine,
	gltut::PhongMaterialModel* phongMaterialModel)
{
	const int COUNT = 3;
	const float GEOMETRY_SIZE = 1.0f;
	const float STRIDE = 3.0f;
	auto* boxMesh = engine.getFactory()->getGeometry()->createBox(
		GEOMETRY_SIZE,
		GEOMETRY_SIZE,
		GEOMETRY_SIZE);

	GLTUT_CHECK(boxMesh, "Failed to create mesh");

	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			const gltut::Vector3 position(
				(i - (COUNT - 1.0f) * 0.5f) * STRIDE,
				GEOMETRY_SIZE * 0.5,
				(j - (COUNT - 1.0f) * 0.5f) * STRIDE);

			auto* object = engine.getScene()->createGeometry(
				boxMesh,
				phongMaterialModel->getMaterial(),
				gltut::Matrix4::translationMatrix(position));
			GLTUT_CHECK(object, "Failed to create object");
		}
	}
}

/// Creates lights
void createLights(
	gltut::Engine& engine,
	gltut::u32 usedPointLights,
	std::vector<gltut::GeometryNode*>& pointLights,
	gltut::GeometryNode*& spotLight)
{
	pointLights.clear();
	spotLight = nullptr;

	gltut::Scene& scene = *engine.getScene();

	auto* lightMesh = engine.getFactory()->getGeometry()->createSphere(0.2f, 10);
	GLTUT_CHECK(lightMesh, "Failed to create light mesh");

	auto* lightShader = engine.getRenderer()->loadShader(
		"assets/light_shader.vs",
		"assets/light_shader.fs");
	GLTUT_CHECK(lightShader, "Failed to create light shader program");

	auto* lightShaderBinding = scene.createShaderBinding(lightShader);
	GLTUT_CHECK(lightShaderBinding, "Failed to create light shader binding");

	gltut::bindModelViewProjectionShaderParameters(lightShaderBinding, "model", "view", "projection");

	const gltut::u32 pointLightCount  = std::min(
		usedPointLights,
		static_cast<gltut::u32>(POINT_LIGHT_POSITIONS.size()));

	for (size_t i = 0; i < pointLightCount; ++i)
	{
		auto* lightMaterial = scene.createMaterial(lightShaderBinding);
		GLTUT_CHECK(lightMaterial, "Failed to create light material");
		lightMaterial->getShaderArguments()->setVec3("lightColor",
			POINT_LIGHT_COLORS[i].r,
			POINT_LIGHT_COLORS[i].g,
			POINT_LIGHT_COLORS[i].b);

		auto* light = scene.createGeometry(lightMesh, lightMaterial);
		GLTUT_CHECK(light, "Failed to create light object");
		light->setTransform(gltut::Matrix4::translationMatrix(POINT_LIGHT_POSITIONS[i]));

		pointLights.push_back(light);

		auto* lightSource = scene.createLight(
			gltut::LightNode::Type::POINT,
			gltut::Matrix4::identity(),
			light);

		lightSource->setAmbient(gltut::Color(
			POINT_LIGHT_COLORS[i].r * 0.2f,
			POINT_LIGHT_COLORS[i].g * 0.2f,
			POINT_LIGHT_COLORS[i].b * 0.2f, 1.0f));

		lightSource->setDiffuse(POINT_LIGHT_COLORS[i]);
		lightSource->setSpecular(POINT_LIGHT_COLORS[i]);

		GLTUT_CHECK(lightSource, "Failed to create light source");
	}

	// Create a spot light
	auto* spotLightMaterial = scene.createMaterial(lightShaderBinding);
	GLTUT_CHECK(spotLightMaterial, "Failed to create spot light material");
	spotLightMaterial->getShaderArguments()->setVec3("lightColor",
		SPOT_LIGHT_COLOR.r,
		SPOT_LIGHT_COLOR.g,
		SPOT_LIGHT_COLOR.b);

	spotLight = scene.createGeometry(
		lightMesh,
		spotLightMaterial,
		gltut::Matrix4::translationMatrix({ 0.0f, SPOT_LIGHT_Y, SPOT_LIGHT_Z }));

	auto* spotLightSource = scene.createLight(
		gltut::LightNode::Type::SPOT,
		gltut::Matrix4::identity(),
		spotLight);

	spotLightSource->setDirection({ 0.0f, -1.0f, -1.0f });
	spotLightSource->setInnerAngle(gltut::toRadians(25.0f));
	spotLightSource->setOuterAngle(gltut::toRadians(30.0f));
	spotLightSource->setAmbient({ 0.5f, 0.5f, 0.5f, 1.0f });
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

		gltut::PhongMaterialModel* phongMaterialModel = engine->getFactory()->getMaterial()->createPhongModel();
		GLTUT_CHECK(phongMaterialModel, "Failed to create Phong material model");

		gltut::Texture* diffuseTexture = renderer->loadTexture("assets/container2.png");
		GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

		gltut::Texture* specularTexture = renderer->loadTexture("assets/container2_specular.png");
		GLTUT_CHECK(specularTexture, "Failed to create specular texture");

		phongMaterialModel->setDiffuse(diffuseTexture);
		phongMaterialModel->setSpecular(specularTexture);

		auto* floorGeometry = engine->getFactory()->getGeometry()->createBox(20.0f, 1.0f, 20.0f);
		GLTUT_CHECK(floorGeometry, "Failed to create floor geometry");
		scene->createGeometry(
			floorGeometry,
			phongMaterialModel->getMaterial(),
			gltut::Matrix4::translationMatrix({ 0.0f, -0.5f, 0.0f }));

		createBoxes(*engine, phongMaterialModel);

		const gltut::u32 usedPointLights = 3; // Change this to use more or fewer lights
		std::vector<gltut::GeometryNode*> pointLights;
		gltut::GeometryNode* spotLight = nullptr;
		createLights(*engine, usedPointLights, pointLights, spotLight);

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

			for (size_t i = 0; i < pointLights.size(); ++i)
			{
				const gltut::Vector3 lightRotation = time * POINT_LIGHT_ROTATIONS[i];
				gltut::Matrix4 lightTransform =
					gltut::Matrix4::rotationMatrix(lightRotation) *
					gltut::Matrix4::translationMatrix(POINT_LIGHT_POSITIONS[i]);
				pointLights[i]->setTransform(lightTransform);
			}

			float spotLightHeight = (std::cos(time) * 0.5f + 0.5f) * SPOT_LIGHT_Y;
			spotLight->setTransform(
				gltut::Matrix4::translationMatrix({ 0.0f, spotLightHeight, SPOT_LIGHT_Z }));

			if (!engine->update())
			{
				break;
			}
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
