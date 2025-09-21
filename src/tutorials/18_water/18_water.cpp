// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "imgui/EngineImgui.h"

static const char* WATER_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 inPosition;

out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

struct Wave
{
	float amplitude;
	float waveNumber;
	float frequency;
	float phase;
	vec2 direction;
};

#define WAVE_COUNT 4
uniform Wave waves[WAVE_COUNT];

void main()
{
	position = inPosition;
	for (int i = 0; i < WAVE_COUNT; ++i)
	{
		if (waves[i].amplitude > 0.0)
		{
			float theta = 
				dot(waves[i].direction, inPosition.xy) * waves[i].waveNumber + 
				time * waves[i].frequency +
				waves[i].phase;
			position.z += waves[i].amplitude * sin(theta);
		}
	}
	gl_Position = model * vec4(position, 1.0);
	gl_Position = projection * view * gl_Position;
}
)";

static const char* WATER_FRAGMENT_SHADER = R"(
#version 330 core
in vec3 position;
out vec4 outColor;

struct Wave
{
	float amplitude;
	float waveNumber;
	float frequency;
	float phase;
	vec2 direction;
};

#define WAVE_COUNT 4
uniform Wave waves[WAVE_COUNT];

uniform mat4 model;
uniform float time;
uniform vec3 lightDir;
uniform vec3 viewPos;

void main()
{
	float df_dx = 0.0f;
	float df_dy = 0.0f;
	for (int i = 0; i < WAVE_COUNT; ++i)
	{
		if (waves[i].amplitude > 0.0)
		{
			float amplitude = waves[i].amplitude;
			float waveNumber = waves[i].waveNumber;
			vec2 direction = waves[i].direction;

			float theta = 
				dot(direction, position.xy) * waveNumber + 
				time * waves[i].frequency +
				waves[i].phase;

			df_dx += amplitude * waveNumber * direction.x * cos(theta);
			df_dy += amplitude * waveNumber * direction.y * cos(theta);
		}
	}
	vec3 tangent = normalize(vec3(1.0f, 0.0f, df_dx));
	vec3 bitangent = normalize(vec3(0.0f, 1.0f, df_dy));
	vec3 normal = cross(tangent, bitangent);
	normal = normalize(mat3(model) * normal);
	float diffuse = max(dot(normal, -lightDir), 0.0);

	vec3 reflectDir = normalize(reflect(lightDir, normal));

	vec3 globalPos = vec3(model * vec4(position, 1.0));
	vec3 viewDir = normalize(viewPos - globalPos);
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec3 diffuseColor = vec3(0x35 / 255.0f, 0x80 / 255.0f, 0xBB / 255.0f);
	vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);
	vec3 specularColor = vec3(0.5f, 0.5f, 0.5f);	

	// Diffuse + Specular + Ambient
	outColor = vec4(diffuseColor * diffuse + specularColor * specular + ambientColor, 1.0f);
}
)";

struct Wave
{
	float amplitude;
	float period;
	float phase;
	gltut::Vector2 direction;
};

static std::array<Wave, 2> waves = {
	Wave {5.0f, 5.0f, 0.0f, gltut::Vector2(1.0f, 0.0f)},
	Wave {5.0f, 5.0f, 0.0f, gltut::Vector2(-1.0f, 0.0f)}};

static float getInfiniteWaterDepthWaveNumber(
	float wavePeriod,
	float gravityAcceleration)
{
	GLTUT_ASSERT(wavePeriod > 0.0);
	GLTUT_ASSERT(gravityAcceleration > 0.0);
	const float frequency = float(2.0) * gltut::PI / wavePeriod;
	return (frequency * frequency) / gravityAcceleration;
}

static constexpr float GRAVITY_ACCELERATION = 9.81f;

gltut::Material* createWaterMaterial(
	gltut::Renderer* renderer,
	gltut::TextureCubemap*)
{
	gltut::ShaderRendererBinding* shaderBinding = gltut::createStandardShaderBinding(
		renderer,
		WATER_VERTEX_SHADER,
		WATER_FRAGMENT_SHADER);

	shaderBinding->bind(
		gltut::RendererBinding::Parameter::VIEWPOINT_POSITION,
		"viewPos");

	gltut::Shader* shader = shaderBinding->getTarget();
	size_t usedWaves = 2;
	for (size_t i = 0; i < usedWaves; ++i)
	{
		std::string baseName = "waves[" + std::to_string(i) + "]";
		shader->setFloat((baseName + ".amplitude").c_str(), waves[i].amplitude);

		const float waveNumber = getInfiniteWaterDepthWaveNumber(
			waves[i].period,
			GRAVITY_ACCELERATION);
		shader->setFloat((baseName + ".waveNumber").c_str(), waveNumber);

		shader->setFloat((baseName + ".frequency").c_str(), 2.0f * gltut::PI / waves[i].period);
		shader->setFloat((baseName + ".phase").c_str(), waves[i].phase);

		const gltut::Vector2 dir = waves[i].direction.getNormalized();
		shader->setVec2((baseName + ".direction").c_str(), dir.x, dir.y);
	}
	GLTUT_CHECK(shaderBinding != nullptr, "Failed to create shader binding");

	gltut::Material* waterMaterial = renderer->createMaterial();
	GLTUT_CHECK(waterMaterial != nullptr, "Failed to create refractive material");

	gltut::MaterialPass* pass = waterMaterial->createPass(0, shaderBinding, 1, 0);
	GLTUT_CHECK(pass != nullptr, "Failed to create material pass");

	return waterMaterial;
}

///	The program entry point
int main()
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Cubemap");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

		gltut::TextureCubemap* skyboxTexture = engine->getDevice()->getTextures()->load(
			"assets/skybox/left.jpg",
			"assets/skybox/right.jpg",
			"assets/skybox/bottom.jpg",
			"assets/skybox/top.jpg",
			"assets/skybox/back.jpg",
			"assets/skybox/front.jpg",
			gltut::TextureParameters(
				gltut::TextureFilterMode::LINEAR,
				gltut::TextureFilterMode::LINEAR,
				gltut::TextureWrapMode::CLAMP_TO_EDGE));

		gltut::Camera* camera = engine->getScene()->createCamera(
			{0.0f, 10.0f, 100.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			45.0f,
			0.1f,
			1000.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera, 0.2f, 100.0f, 1.0f, 1000.0f));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		const bool skyboxCreated = engine->getFactory()->getScene()->createSkybox(
			skyboxTexture,
			scene->getActiveCameraViewpoint(),
			nullptr);

		GLTUT_CHECK(skyboxCreated, "Failed to create skybox");

		auto* waterMaterial = createWaterMaterial(
			engine->getRenderer(),
			skyboxTexture);

		auto* waterPlaneMesh = engine->getFactory()->getGeometry()->createPlane(
			{100.0f, 100.0f},
			{200, 200},
			{false, false, false});

		GLTUT_CHECK(waterPlaneMesh != nullptr, "Failed to create water plane geometry");

		engine->getScene()->createGeometry(
			waterPlaneMesh,
			waterMaterial,
			gltut::Matrix4::rotationMatrix({gltut::toRadians(-90.0f), 0.0f, 0.0f}));

		float lightAzimuth = -90.0f;
		float lightInclination = 45.0f;
		bool firstSetup = true;
		gltut::Vector3 lightDir = {0.0f, 0.0f, 0.0f};

		auto start = std::chrono::high_resolution_clock::now();
		do
		{
			auto time = std::chrono::duration<float>(
							std::chrono::high_resolution_clock::now() - start)
							.count();

			waterMaterial->getPass(0)->getShaderArguments()->setFloat("time", time);

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
				lightDir = gltut::setDistanceAzimuthInclination(
					{1.0f,
					 azimuthRad,
					 inclinationRad});
				firstSetup = false;
			}
			ImGui::End();

			// Set the light direction in the water shader
			waterMaterial->getPass(0)->getShaderArguments()->setVec3(
				"lightDir",
				-lightDir.x,
				-lightDir.z,
				-lightDir.y);

		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
