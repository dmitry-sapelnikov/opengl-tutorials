// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"

namespace
{
// Local constants
/// Point light positions
const std::vector<gltut::Vector3> POINT_LIGHT_POSITIONS = {
	{0.0, 10.0f, 20.0f},
	{5.0, 0.0f, 0.0f},
	{0.0, 5.0f, 0.0f}};

/// Point light colors
const std::vector<gltut::Color> POINT_LIGHT_COLORS = {
	{1.0f, 1.0f, 1.0f}, // White light
	{1.0f, 0.5f, 0.5f}, // Red light
	{0.5f, 0.5f, 1.0f}	// Blue light
};

/// Point light rotation axes
const std::vector<gltut::Vector3> POINT_LIGHT_ROTATIONS = {
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, -0.5f},
	{1.5f, 0.0f, 0.0f},
};

/// Directional light color
const gltut::Color directionalLightColor = {1.0f, 1.0f, 0.9f}; // Slightly yellowish light

/// Spot light color
const gltut::Color SPOT_LIGHT_COLOR = {1.0f, 1.0f, 1.0f}; // White light

/// Spot light y position
constexpr float SPOT_LIGHT_Y = 10.0f;

/// Spot light z position
constexpr float SPOT_LIGHT_Z = 6.0f;

// Local functions
/// Creates boxes
void createBoxes(
	gltut::Engine& engine,
	gltut::PhongMaterialModel* phongMaterialModel)
{
	const int COUNT = 3;
	const float GEOMETRY_SIZE = 1.0f;
	const float STRIDE = 3.0f;
	auto* boxGeometry = engine.getFactory()->getGeometry()->createBox(gltut::Vector3(GEOMETRY_SIZE));

	GLTUT_CHECK(boxGeometry, "Failed to create geometry");

	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			const gltut::Vector3 position(
				(i - (COUNT - 1.0f) * 0.5f) * STRIDE,
				GEOMETRY_SIZE * 0.5,
				(j - (COUNT - 1.0f) * 0.5f) * STRIDE);

			auto* object = engine.getScene()->createGeometry(
				boxGeometry,
				phongMaterialModel->getMaterial(),
				gltut::Matrix4::translationMatrix(position));
			GLTUT_CHECK(object, "Failed to create object");
		}
	}
}

/// Creates a light source + its visual representation
gltut::GeometryNode* createLight(
	gltut::Engine& engine,
	gltut::Geometry* lightGeometry,
	const gltut::LightNode::Type lightType,
	const gltut::Vector3& position,
	const gltut::Color& color)
{
	auto* colorTexture = engine.getDevice()->getTextures()->createSolidColor(color);
	GLTUT_CHECK(colorTexture, "Failed to create color texture");

	auto* lightMaterial = engine.getFactory()->getMaterial()->createFlatColorMaterial();
	GLTUT_CHECK(lightMaterial, "Failed to create light material");
	lightMaterial->setColor(colorTexture);

	auto* light = engine.getScene()->createGeometry(lightGeometry, lightMaterial->getMaterial());
	GLTUT_CHECK(light, "Failed to create light object");
	light->setTransform(gltut::Matrix4::translationMatrix(position));

	auto* lightSource = engine.getScene()->createLight(lightType, gltut::Matrix4::identity(), light);
	lightSource->setAmbient(gltut::Color(color.r * 0.2f, color.g * 0.2f, color.b * 0.2f, 1.0f));
	lightSource->setDiffuse(color);
	lightSource->setSpecular(color);

	return light;
}

/// Creates the lights in the scene
void createLights(
	gltut::Engine& engine,
	gltut::u32 usedPointLights,
	gltut::GeometryNode* directionalLight,
	std::vector<gltut::GeometryNode*>& pointLights,
	gltut::GeometryNode*& spotLight)
{
	directionalLight = nullptr;
	pointLights.clear();
	spotLight = nullptr;

	auto* lightGeometry = engine.getFactory()->getGeometry()->createSphere(0.2f, 10);
	GLTUT_CHECK(lightGeometry, "Failed to create light geometry");

	// Create a directional light]
	directionalLight = createLight(
		engine,
		lightGeometry,
		gltut::LightNode::Type::DIRECTIONAL,
		gltut::Vector3(0.0f, 10.0f, 0.0f),
		directionalLightColor);

	GLTUT_CHECK(directionalLight, "Failed to create directional light");
	gltut::LightNode* directionalLightSource = dynamic_cast<gltut::LightNode*>(directionalLight->getChild(0));
	GLTUT_CHECK(directionalLightSource, "Failed to get directional light source");
	directionalLightSource->setDirection({-3.0f, -1.0f, 0.0f});

	const gltut::u32 pointLightCount = std::min(
		usedPointLights,
		static_cast<gltut::u32>(POINT_LIGHT_POSITIONS.size()));

	for (size_t i = 0; i < pointLightCount; ++i)
	{
		const gltut::Vector3& position = POINT_LIGHT_POSITIONS[i];
		const gltut::Color& color = POINT_LIGHT_COLORS[i % POINT_LIGHT_COLORS.size()];
		auto* pointLight = createLight(
			engine,
			lightGeometry,
			gltut::LightNode::Type::POINT,
			position,
			color);
		GLTUT_CHECK(pointLight, "Failed to create point light");
		pointLights.push_back(pointLight);
	}

	// Create a spot light
	spotLight = createLight(
		engine,
		lightGeometry,
		gltut::LightNode::Type::SPOT,
		gltut::Vector3(0.0f, SPOT_LIGHT_Y, SPOT_LIGHT_Z),
		SPOT_LIGHT_COLOR);

	GLTUT_CHECK(spotLight, "Failed to create spot light");
	gltut::LightNode* spotLightSource = dynamic_cast<gltut::LightNode*>(spotLight->getChild(0));
	GLTUT_CHECK(spotLightSource, "Failed to get spot light source");
	spotLightSource->setDirection({0.0f, -1.0f, -1.0f});
	spotLightSource->setInnerAngle(gltut::toRadians(25.0f));
	spotLightSource->setOuterAngle(gltut::toRadians(30.0f));
	spotLightSource->setLinearAttenuation(0.1f);
	spotLightSource->setQuadraticAttenuation(0.01f);
	spotLightSource->setAmbient({0.5f, 0.5f, 0.5f, 1.0f});
}

// End of the anonymous namespace
}

/// The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine, "Failed to create engine");

		engine->getWindow()->setTitle("Lighting");
		engine->getWindow()->showFPS(true);

		auto* device = engine->getDevice();
		auto* scene = engine->getScene();

		auto* materialFactory = engine->getFactory()->getMaterial();

		auto* phongShader = materialFactory->createPhongShader(
			1,	// No directional lights
			3,	// Use 3 point lights
			1); // Use 1 spot light

		GLTUT_CHECK(phongShader, "Failed to create Phong shader");

		gltut::PhongMaterialModel* phongMaterialModel = materialFactory->createPhongMaterial(phongShader);
		GLTUT_CHECK(phongMaterialModel, "Failed to create Phong material model");

		gltut::Texture* diffuseTexture = device->getTextures()->load("assets/container2.png");
		GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

		gltut::Texture* specularTexture = device->getTextures()->load("assets/container2_specular.png");
		GLTUT_CHECK(specularTexture, "Failed to create specular texture");

		phongMaterialModel->setDiffuse(diffuseTexture);
		phongMaterialModel->setSpecular(specularTexture);

		auto* floorGeometry = engine->getFactory()->getGeometry()->createBox({20.0f, 1.0f, 20.0f});
		GLTUT_CHECK(floorGeometry, "Failed to create floor geometry");
		scene->createGeometry(
			floorGeometry,
			phongMaterialModel->getMaterial(),
			gltut::Matrix4::translationMatrix({0.0f, -0.5f, 0.0f}));

		createBoxes(*engine, phongMaterialModel);

		const gltut::u32 usedPointLights = 3;
		gltut::GeometryNode* directionalLight = nullptr;
		std::vector<gltut::GeometryNode*> pointLights;
		gltut::GeometryNode* spotLight = nullptr;
		createLights(*engine, usedPointLights, directionalLight, pointLights, spotLight);

		gltut::Camera* camera = engine->getScene()->createCamera(
			{-2.0f, 2.0f, 6.0f},
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
				gltut::Matrix4::translationMatrix({0.0f, spotLightHeight, SPOT_LIGHT_Z}));

			if (!engine->update())
			{
				break;
			}
		}
	}
	GLTUT_APPLICATION_CATCH;
	return 0;
}
