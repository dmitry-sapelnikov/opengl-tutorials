// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"
#include "engine/math/Rng.h"

#include "imgui/EngineImgui.h"

namespace
{

// Local constants
/// Directional light position
const gltut::Vector3 DIR_LIGHT_POSITION = {0.0f, 0.0f, 10.0f};

/// Directional light color
const gltut::Color DIR_LIGHT_COLOR = {1.0f, 1.0f, 1.0f};

// Local functions
/// Creates a Phong material model
gltut::PhongMaterialModel* createPhongMaterialModel(gltut::Engine& engine)
{
	gltut::MaterialFactory* materialFactory = engine.getFactory()->getMaterial();
	auto* phongShader = materialFactory->createPhongShader(1, 0, 0);
	GLTUT_CHECK(phongShader, "Failed to create Phong shader");

	gltut::PhongMaterialModel* phongMaterialModel = materialFactory->createPhongMaterial(phongShader);
	GLTUT_CHECK(phongMaterialModel, "Failed to create Phong material model");

	gltut::GraphicsDevice* device = engine.getDevice();
	gltut::Texture* diffuseTexture = device->getTextures()->load("assets/brickwall.jpg");
	GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");
	phongMaterialModel->setDiffuse(diffuseTexture);

	const gltut::Texture* specularTexture = device->getTextures()->createSolidColor({
		0.5f,
		0.5f,
		0.5f,
	});
	GLTUT_CHECK(specularTexture, "Failed to create specular texture");
	phongMaterialModel->setSpecular(const_cast<gltut::Texture*>(specularTexture));

	gltut::Texture* normalTexture = device->getTextures()->load("assets/brickwall_normal.jpg");
	GLTUT_CHECK(normalTexture, "Failed to create normal texture");
	phongMaterialModel->setNormal(normalTexture);

	phongMaterialModel->setShininess(32.0f);
	return phongMaterialModel;
}

/// Creates a light source + its visual representation
std::pair<gltut::GeometryNode*, gltut::LightNode*> createLight(gltut::Engine& engine)
{
	auto* lightGeometry = engine.getFactory()->getGeometry()->createSphere(0.5f, 16);
	GLTUT_CHECK(lightGeometry, "Failed to create light geometry");

	auto* lightMaterial = engine.getFactory()->getMaterial()->createFlatColorMaterial(false);
	GLTUT_CHECK(lightMaterial, "Failed to create light material");
	lightMaterial->setColor(engine.getDevice()->getTextures()->createSolidColor(DIR_LIGHT_COLOR));

	auto* light = engine.getScene()->createGeometry(lightGeometry, lightMaterial->getMaterial());
	GLTUT_CHECK(light, "Failed to create light object");

	light->setTransform(gltut::Matrix4::translationMatrix(DIR_LIGHT_POSITION));
	auto* lightSource = engine.getScene()->createLight(
		gltut::LightNode::Type::DIRECTIONAL,
		gltut::Matrix4::identity(),
		light);

	lightSource->setTarget(-DIR_LIGHT_POSITION);
	lightSource->setAmbient({0.0f, 0.0f, 0.0f});
	lightSource->setDiffuse(DIR_LIGHT_COLOR);
	lightSource->setSpecular(DIR_LIGHT_COLOR);

	return {light, lightSource};
}

// End of the anonymous namespace
}

/// The program entry point
int main()
{
	gltut::EngineImgui* imgui = nullptr;
	std::unique_ptr<gltut::Engine> engine;

	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine, "Failed to create engine");
		engine->getWindow()->setTitle("Normal Maps");

		// Create the Imgui connector
		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui, "Failed to create ImGui instance");

		auto* scene = engine->getScene();
		gltut::PhongMaterialModel* phongMaterialModel = createPhongMaterialModel(*engine);

		auto* floorGeometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(10.0f));
		GLTUT_CHECK(floorGeometry, "Failed to create floor geometry");

		scene->createGeometry(
			floorGeometry,
			phongMaterialModel->getMaterial(),
			gltut::Matrix4::translationMatrix({0.0f, -0.5f, 0.0f}));

		auto [lightNode, lightSource] = createLight(*engine);

		gltut::Camera* camera = engine->getScene()->createCamera(
			{-10.0f, 10.0f, 30.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			45.0f,
			0.1f,
			150.0f);
		GLTUT_CHECK(camera, "Failed to create camera");

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		float lightAzimuth = 0.0f;
		float lightInclination = 0.0f;
		bool firstSetup = true;
		do
		{
			imgui->newFrame();
			ImGui::SetNextWindowPos({10, 10}, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({200, 400}, ImGuiCond_FirstUseEver);
			ImGui::Begin("Settings");

			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());

			// Right azimuth numeric control with range 0 to 360 degrees
			bool azimuthChanged = ImGui::SliderFloat(
				"Light Azimuth",
				&lightAzimuth,
				-180.0f,
				180.0f,
				"%.1f degrees");

			bool inlinationChanged = ImGui::SliderFloat(
				"Light Inclination",
				&lightInclination,
				-90.0f,
				90.0f,
				"%.1f degrees");

			if (firstSetup || azimuthChanged || inlinationChanged)
			{
				const float azimuthRad = gltut::toRadians(lightAzimuth);
				const float inclinationRad = gltut::toRadians(lightInclination);
				const gltut::Matrix4 rotation =
					gltut::Matrix4::rotationMatrix({0.0f, azimuthRad, 0.0f}) *
					gltut::Matrix4::rotationMatrix({-inclinationRad, 0.0f, 0.0f});

				lightNode->setTransform(rotation * gltut::Matrix4::translationMatrix({0.0, 0.0f, 20.0f}));
				firstSetup = false;
			}

			ImGui::End();
		} while (engine->update());
	}
	GLTUT_CATCH_ALL("Failed to run 11_normal_maps example");

	gltut::deleteEngineImgui(imgui);
	return 0;
}
