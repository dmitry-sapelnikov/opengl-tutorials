// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"
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

#define WAVE_COUNT 1
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
	position = vec3(gl_Position);
	gl_Position = projection * view * gl_Position;
}
)";

static const char* WATER_FRAGMENT_SHADER = R"(
#version 330 core
in vec3 position;
out vec4 outColor;

void main()
{
	outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

struct Wave
{
	float amplitude;
	float period;
	float phase;
	gltut::Vector2 direction;
};

static std::array<Wave, 1> waves = {
	Wave{ 1.0f, 5.0f, 0.0f, gltut::Vector2(1.0f, 0.0f) }
};

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

	gltut::Shader* shader = shaderBinding->getTarget();
	for (size_t i = 0; i < waves.size(); ++i)
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
			{ 0.0f, 0.0f, 20.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			1000.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
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

		(*waterMaterial)[0]->setPolygonFill(
			gltut::PolygonFillMode::LINE,
			1.0f,
			false);

		auto* waterPlaneMesh = engine->getFactory()->getGeometry()->createPlane(
			{ 1000.0f, 1000.0f },
			{ 200, 200 },
			{ false, false, false });

		GLTUT_CHECK(waterPlaneMesh != nullptr, "Failed to create water plane geometry");

		engine->getScene()->createGeometry(
			waterPlaneMesh,
			waterMaterial,
			gltut::Matrix4::rotationMatrix({ gltut::toRadians(-90.0f), 0.0f, 0.0f }));

		auto start = std::chrono::high_resolution_clock::now();
		do
		{
			auto time = std::chrono::duration<float>(
				std::chrono::high_resolution_clock::now() - start).count();

			waterMaterial->getPass(0)->getShaderArguments()->setFloat("time", time);

			imgui->newFrame();
			ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({ 200, 400 }, ImGuiCond_FirstUseEver);
			ImGui::Begin("Settings");
			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());
			ImGui::End();
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
