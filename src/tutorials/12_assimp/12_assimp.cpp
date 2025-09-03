// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"
#include "asset_loader/AssetLoader.h"

#include "imgui/EngineImgui.h"


// Slightly yellowish light
constexpr size_t DIRECTIONAL_LIGHT_COUNT = 2;
constexpr size_t USED_DIRECTIONAL_LIGHT_COUNT = 1;
static_assert(
	DIRECTIONAL_LIGHT_COUNT >= USED_DIRECTIONAL_LIGHT_COUNT,
	"Used directional light count must be less than or equal to the total directional light count");

const gltut::Vector3 DIR_LIGHT_POSITIONS[DIRECTIONAL_LIGHT_COUNT] = {
	{ 0.0f, 0.0f, 5.0f },
	{ -2.0f, 2.0f, 3.0f } };

const gltut::Color DIR_LIGHT_COLORS[DIRECTIONAL_LIGHT_COUNT] = {
	{ 1.5f, 1.5f, 1.5f },
	{ 1.2f, 1.2f, 1.2f } };

const bool DIR_LIGHT_CAST_SHADOWS[DIRECTIONAL_LIGHT_COUNT] = {
	true, // First light casts shadows
	false // Second light does not cast shadows
};


/// Creates light
std::pair<gltut::GeometryNode*, gltut::LightNode*> createLight(
	gltut::Scene& scene,
	const gltut::Material& material,
	const gltut::Geometry& geometry,
	const gltut::LightNode::Type lightType,
	const gltut::Vector3& position,
	const gltut::Color& color)
{
	auto* light = scene.createGeometry(&geometry, &material);
	GLTUT_CHECK(light, "Failed to create light object");
	light->setTransform(gltut::Matrix4::translationMatrix(position));

	auto* lightSource = scene.createLight(lightType, gltut::Matrix4::identity(), light);
	lightSource->setTarget(-position);
	lightSource->setAmbient({ 0.2f * color.r, 0.2f * color.g, 0.2f * color.b, 1.0f });
	lightSource->setDiffuse(color);
	lightSource->setSpecular(color);

	return { light, lightSource };
}

void createLights(
	gltut::Engine& engine,
	std::vector<gltut::GeometryNode*>& lights,
	std::vector<gltut::LightNode*>& lightSources,
	std::vector<gltut::ShadowMap*>& shadows)
{
	auto* factory = engine.getFactory();
	auto* lightGeometry = factory->getGeometry()->createSphere(0.5f, 16);
	GLTUT_CHECK(lightGeometry, "Failed to create light geometry");

	for (size_t i = 0; i < USED_DIRECTIONAL_LIGHT_COUNT; ++i)
	{
		// Create a flat color material for the light. This material does not cast shadows.
		auto* lightMaterial = factory->getMaterial()->createFlatColorMaterial(false);
		GLTUT_CHECK(lightMaterial, "Failed to create light material");
		lightMaterial->setColor(engine.getDevice()->getTextures()->createSolidColor(
			DIR_LIGHT_COLORS[i]));

		const auto [light, lightSource] = createLight(
			*engine.getScene(),
			*lightMaterial->getMaterial(),
			*lightGeometry,
			gltut::LightNode::Type::DIRECTIONAL,
			DIR_LIGHT_POSITIONS[i],
			DIR_LIGHT_COLORS[i]);

		lights.push_back(light);
		lightSources.push_back(lightSource);

		gltut::ShadowMap* shadow = factory->getScene()->createShadowMap(
			lightSource,
			engine.getScene()->getRenderGroup(),
			10.0f, // Frustum size
			1.5f,  // Near plane
			50.0f, // Far plane
			2048);  // Shadow map size
		GLTUT_CHECK(shadow, "Failed to create shadow map");
		lightSource->setShadowMap(shadow);

		shadows.push_back(shadow);
	}
}

///	The program entry point
int main()
{
	gltut::EngineImgui* imgui = nullptr;
	gltut::AssetMaterialFactory* assetMaterialFactory = nullptr;
	gltut::AssetLoader* assetLoader = nullptr;
	std::unique_ptr<gltut::Engine> engine;

	GLTUT_CATCH_ALL_BEGIN
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine, "Failed to create engine");

		assetLoader = gltut::createAssetLoader(engine.get());

		engine->getWindow()->setTitle("Normal Maps");

		// Create the Imgui connector
		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui, "Failed to create ImGui instance");

		gltut::MaterialFactory* materialFactory = engine->getFactory()->getMaterial();
		auto* phongShader = materialFactory->createPhongShader(1,0, 0);
		GLTUT_CHECK(phongShader, "Failed to create Phong shader");
		
		assetMaterialFactory = gltut::createPhongAssetMaterialFactory(
			materialFactory,
			phongShader,
			true);

		auto* backpack = assetLoader->loadAsset("assets/backpack/backpack.obj", assetMaterialFactory);
		backpack->setTransform(gltut::Matrix4::scaleMatrix({ 2.0f, 2.0f, 2.0f }));

		std::vector<gltut::GeometryNode*> lights;
		std::vector<gltut::LightNode*> lightSources;
		std::vector<gltut::ShadowMap*> shadows;
		createLights(*engine, lights, lightSources, shadows);

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ -10.0f, 10.0f, 30.0f },
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
		float lightAzimuth = 0.0f;
		float lightInclination = 0.0f;

		bool firstSetup = true;
		while (true)
		{
			const auto now = std::chrono::high_resolution_clock::now();
			const float time = std::chrono::duration<float>(now - startTime).count();

			imgui->newFrame();
			ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({ 200, 400 }, ImGuiCond_FirstUseEver);
			ImGui::Begin("Settings");

			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());
			ImGui::Text("Time: %.2f seconds", time);

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
				-89.0f,
				89.0f,
				"%.1f degrees");

			if (firstSetup || azimuthChanged || inlinationChanged)
			{
				const float azimuthRad = gltut::toRadians(lightAzimuth);
				const float inclinationRad = gltut::toRadians(lightInclination);
				const gltut::Matrix4 rotation =
					gltut::Matrix4::rotationMatrix({ 0.0f, azimuthRad, 0.0f }) *
					gltut::Matrix4::rotationMatrix({ -inclinationRad, 0.0f, 0.0f });

				lights[0]->setTransform(rotation * gltut::Matrix4::translationMatrix({ 0.0, 0.0f, 20.0f }));
				firstSetup = false;
			}

			// Display the shadow map textures
			ImGui::Text("Shadow Maps:");
			for (size_t i = 0; i < shadows.size(); ++i)
			{
				ImGui::Text("Shadow Map %zu", i);
				ImGui::Image(
					shadows[i]->getTexture()->getId(),
					{ 400, 400 },
					{ 0, 1 }, { 1, 0 });
			}

			ImGui::End();

			if (!engine->update())
			{
				break;
			}
		}
	GLTUT_CATCH_ALL_END("Failed to run 12 assimp example");

	gltut::deleteEngineImgui(imgui);
	gltut::deleteAssetLoader(assetLoader);
	gltut::deleteAssetMaterialFactory(assetMaterialFactory);

	return 0;
}
