// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"

#include "imgui/EngineImgui.h"


// Slightly yellowish light
constexpr size_t DIRECTIONAL_LIGHT_COUNT = 2;

const gltut::Vector3 DIR_LIGHT_POSITIONS[DIRECTIONAL_LIGHT_COUNT] = {
	{ 10.0f, 5.0f, 0.0f },
	{ -5.0f, 5.0f, 15.0f } };

const gltut::Color DIR_LIGHT_COLORS[DIRECTIONAL_LIGHT_COUNT] = {
	{ 1.5f, 1.5f, 1.5f },
	{ 1.2f, 1.2f, 1.2f } };

/// Creates boxes
void createBoxes(
	gltut::Engine& engine,
	gltut::PhongMaterialModel* phongMaterialModel)
{
	const int COUNT = 3;
	const float GEOMETRY_SIZE = 1.0f;
	const float STRIDE = 3.0f;
	auto* boxGeometry = engine.getFactory()->getGeometry()->createBox(
		GEOMETRY_SIZE, GEOMETRY_SIZE, GEOMETRY_SIZE);
	GLTUT_CHECK(boxGeometry, "Failed to create geometry");

	gltut::Rng rng;
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			const float size = rng.nextFloat(0.5f, 2.0f);
			const gltut::Vector3 position(
				(i - (COUNT - 1.0f) * 0.5f) * STRIDE,
				0.5f * size,
				(j - (COUNT - 1.0f) * 0.5f) * STRIDE);

			auto* object = engine.getScene()->createGeometry(
				boxGeometry,
				phongMaterialModel->getMaterial(),
				gltut::Matrix4::transformMatrix(
					position,
					{ 0.0f, 0.0, 0.0f },
					size * gltut::Vector3(1.0f, 1.0f, 1.0f)));

			GLTUT_CHECK(object, "Failed to create object");
		}
	}
}

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
	lightSource->setAmbient(gltut::Color(color.r * 0.2f, color.g * 0.2f, color.b * 0.2f, 1.0f));
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
	auto* lightGeometry = engine.getFactory()->getGeometry()->createSphere(0.5f, 16);
	GLTUT_CHECK(lightGeometry, "Failed to create light geometry");

	for (size_t i = 0; i < DIRECTIONAL_LIGHT_COUNT; ++i)
	{
		auto* lightMaterial = engine.getFactory()->getMaterial()->createFlatColorMaterial();
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

		gltut::ShadowMap* shadow = engine.getFactory()->getShadow()->createShadowMap(
			lightSource,
			engine.getScene()->getRenderObject(),
			40.0f, // Frustum size
			0.5f,  // Near plane
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
	std::unique_ptr<gltut::Engine> engine;

	GLTUT_CATCH_ALL_BEGIN
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine, "Failed to create engine");

		engine->getWindow()->setTitle("Lighting");

		// Create the Imgui connector
		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui, "Failed to create ImGui instance");

		auto* device = engine->getDevice();
		auto* scene = engine->getScene();

		auto* materialFactory = engine->getFactory()->getMaterial();

		auto* phongShader = materialFactory->createPhongShader(
			2, // 1 directional light
			0, // No point lights
			0); // No spot lights

		GLTUT_CHECK(phongShader, "Failed to create Phong shader");

		gltut::PhongMaterialModel* phongMaterialModel = materialFactory->createPhongMaterial(phongShader);
		GLTUT_CHECK(phongMaterialModel, "Failed to create Phong material model");

		gltut::Texture* diffuseTexture = device->getTextures()->load("assets/container2.png");
		//gltut::Texture* diffuseTexture = device->createSolidColorTexture(1.0f, 0.5f, 0.31f, 1.0f);
		GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

		gltut::Texture* specularTexture = device->getTextures()->load("assets/container2_specular.png");
		//device->createSolidColorTexture(0.0f, 0.0f, 0.0f, 1.0f);
		GLTUT_CHECK(specularTexture, "Failed to create specular texture");

		phongMaterialModel->setDiffuse(diffuseTexture);
		phongMaterialModel->setSpecular(specularTexture);
		phongMaterialModel->setShininess(32.0f);

		auto* floorGeometry = engine->getFactory()->getGeometry()->createBox(20.0f, 1.0f, 20.0f);
		GLTUT_CHECK(floorGeometry, "Failed to create floor geometry");
		scene->createGeometry(
			floorGeometry,
			phongMaterialModel->getMaterial(),
			gltut::Matrix4::translationMatrix({ 0.0f, -0.5f, 0.0f }));

		createBoxes(*engine, phongMaterialModel);

		std::vector<gltut::GeometryNode*> lights;
		std::vector<gltut::LightNode*> lightSources;
		std::vector<gltut::ShadowMap*> shadows;
		createLights(*engine, lights, lightSources, shadows);
		
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
		float lightAzimuth = 0.0f;
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
			if (ImGui::SliderAngle(
				"Light Azimuth",
				&lightAzimuth,
				0.0f, 360.0f,
				"%0.1f degrees"))
			{
				gltut::Matrix4 lightTransform =
					gltut::Matrix4::rotationMatrix({ 0, lightAzimuth, 0 }) *
					gltut::Matrix4::translationMatrix(DIR_LIGHT_POSITIONS[0]);

				lights[0]->setTransform(lightTransform);
			}

			// Display the shadow map textures
			ImGui::Text("Shadow Maps:");
			for (size_t i = 0; i < shadows.size(); ++i)
			{
				ImGui::Text("Shadow Map %zu", i);
				ImGui::Image(
					shadows[i]->getTexture()->getId(),
					{ 200, 200 },
					{ 0, 1 }, { 1, 0 });
			}

			ImGui::End();

			if (!engine->update())
			{
				break;
			}
		}
	GLTUT_CATCH_ALL_END("Failed to run 9_shadows example");

	gltut::deleteEngineImgui(imgui);
	return 0;
}
