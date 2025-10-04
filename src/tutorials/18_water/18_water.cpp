// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "imgui/EngineImgui.h"

#include "Waves.h"

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

#define WAVE_COUNT 110
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

#define WAVE_COUNT 110
uniform Wave waves[WAVE_COUNT];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform float zNear;
uniform float zFar;
uniform vec3 deepWaterColor;
uniform float deepWaterDistance;

uniform float time;
uniform samplerCube skyboxSampler;
uniform sampler2D sceneColorSampler;
uniform sampler2D sceneDepthSampler;

#define SAMPLING_STEPS 10

float getGlobalDistance(float depth)
{
	return zNear * (zFar / (zFar + depth * (zNear - zFar)) - 1.0);
}

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
	
	vec3 globalPos = vec3(model * vec4(position, 1.0));
	vec3 viewDir = normalize(globalPos - viewPos);
	vec3 reflectDir = reflect(viewDir, normal);
	vec3 refractDir = refract(viewDir, normal, 1.00 / 1.33);

	//	 Perform path tracing along the refraction direction to get the refracted color
	vec3 refractColor = deepWaterColor;
	vec4 waterSurfaceNcd = projection * view * vec4(globalPos, 1.0);
	waterSurfaceNcd /= waterSurfaceNcd.w;
	float waterSurfaceDepth = waterSurfaceNcd.z * 0.5 + 0.5;
	float sceneDepth = texture(sceneDepthSampler, waterSurfaceNcd.xy * 0.5 + 0.5).r;

	if (sceneDepth > waterSurfaceDepth)
	{
		float distanceFromSurface = getGlobalDistance(sceneDepth) - getGlobalDistance(waterSurfaceDepth);
		if (distanceFromSurface < deepWaterDistance)
		{
			// Fake refraction sampling points
			vec3 samplePos = globalPos + refractDir * distanceFromSurface;

			vec4 samplePosNcd = (projection * view * vec4(samplePos, 1.0));
			samplePosNcd /= samplePosNcd.w;
			vec2 sampleUV = samplePosNcd.xy * 0.5 + 0.5;

			float refractDepth = texture(sceneDepthSampler, sampleUV).r;

			if (refractDepth > waterSurfaceDepth)
			{
				distanceFromSurface = getGlobalDistance(refractDepth) - getGlobalDistance(waterSurfaceDepth);
				refractColor = mix(
					texture(sceneColorSampler, sampleUV).rgb,
					deepWaterColor,
					clamp(distanceFromSurface / deepWaterDistance, 0.0, 1.0));
			}
		}
	}
	vec3 reflectColor = texture(skyboxSampler, reflectDir).rgb;
	float fresnel = max(0.0, dot(-viewDir, normal));
	outColor = vec4(mix(reflectColor, refractColor, fresnel), 1.0);
}
)";


// Texture to window trivial fragment shader// Grayscale fragment shader
static const char* TEXTURE_TO_WINDOW_FRAGMENT_SHADER = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D colorSampler;
uniform sampler2D depthSampler;
uniform sampler2D waterColorSampler;
uniform sampler2D waterDepthSampler;

void main()
{
	if (texture(depthSampler, texCoord).r <= texture(waterDepthSampler, texCoord).r)
	{
		outColor = texture(colorSampler, texCoord);
	}
	else
	{
		outColor = texture(waterColorSampler, texCoord);
	}
})";


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

static const std::array<gltut::Wave, 10> WAVES =
{
	gltut::Wave(0.15f, 6.0f, 0.0f, gltut::Vector2(1.0f, 0.0f)),
	gltut::Wave(0.10f, 5.0f, 1.0f, gltut::Vector2(0.8f, 0.6f)),
	gltut::Wave(0.08f, 4.5f, 2.0f, gltut::Vector2(0.6f, 0.8f)),
	gltut::Wave(0.05f, 3.0f, 3.0f, gltut::Vector2(0.4f, 0.9f)),
	gltut::Wave(0.03f, 2.7f, 4.0f, gltut::Vector2(0.2f, 1.0f)),
	gltut::Wave(0.02f, 2.5f, 5.0f, gltut::Vector2(-0.2f, 1.0f)),
	gltut::Wave(0.01f, 2.3f, 6.0f, gltut::Vector2(-0.4f, 0.9f)),
	gltut::Wave(0.008f, 2.2f, 7.0f, gltut::Vector2(-0.6f, 0.8f)),
	gltut::Wave(0.005f, 2.15f, 8.0f, gltut::Vector2(-0.8f, 0.6f)),
	gltut::Wave(0.003f, 2.1f, 9.0f, gltut::Vector2(-1.0f, 0.0f))
};

gltut::Material* createWaterMaterial(
	gltut::Renderer* renderer,
	gltut::TextureCubemap* skyboxTexture,
	gltut::Texture2* sceneColorTexture,
	gltut::Texture2* sceneDepthTexture)
{
	gltut::ShaderRendererBinding* shaderBinding = gltut::createStandardShaderBinding(
		renderer,
		WATER_VERTEX_SHADER,
		WATER_FRAGMENT_SHADER);

	shaderBinding->bind(
		gltut::RendererBinding::Parameter::VIEWPOINT_POSITION,
		"viewPos");

	shaderBinding->getTarget()->setInt("skyboxSampler", 0);
	shaderBinding->getTarget()->setInt("sceneColorSampler", 1);
	shaderBinding->getTarget()->setInt("sceneDepthSampler", 2);

	gltut::Shader* shader = shaderBinding->getTarget();

	for (size_t i = 0; i < WAVES.size(); ++i)
	{
		std::string baseName = "waves[" + std::to_string(i) + "]";
		shader->setFloat((baseName + ".amplitude").c_str(), WAVES[i].amplitude);

		const float waveNumber = getInfiniteWaterDepthWaveNumber(
			WAVES[i].period,
			GRAVITY_ACCELERATION);
		shader->setFloat((baseName + ".waveNumber").c_str(), waveNumber);

		shader->setFloat((baseName + ".frequency").c_str(), 2.0f * gltut::PI / WAVES[i].period);
		shader->setFloat((baseName + ".phase").c_str(), WAVES[i].phase);

		const gltut::Vector2 dir = WAVES[i].direction.getNormalized();
		shader->setVec2((baseName + ".direction").c_str(), dir.x, dir.y);
	}
	GLTUT_CHECK(shaderBinding != nullptr, "Failed to create shader binding");

	gltut::Material* waterMaterial = renderer->createMaterial();
	GLTUT_CHECK(waterMaterial != nullptr, "Failed to create refractive material");

	gltut::MaterialPass* pass = waterMaterial->createPass(1, shaderBinding, 3, 0);
	GLTUT_CHECK(pass != nullptr, "Failed to create material pass");
	pass->getTextures()->setTexture(skyboxTexture, 0);
	pass->getTextures()->setTexture(sceneColorTexture, 1);
	pass->getTextures()->setTexture(sceneDepthTexture, 2);

	return waterMaterial;
}

/// Creates a Phong material model
gltut::FlatColorMaterialModel* createMaterialModel(
	gltut::Engine* engine,
	gltut::PhongShaderModel* phongShader)
{
	GLTUT_CHECK(phongShader, "Failed to create Phong shader");

	gltut::MaterialFactory* materialFactory = engine->getFactory()->getMaterial();
	gltut::FlatColorMaterialModel* materialModel = materialFactory->createFlatColorMaterial(phongShader);
	GLTUT_CHECK(materialModel, "Failed to create Phong material model");

	gltut::GraphicsDevice* device = engine->getDevice();
	gltut::Texture* diffuseTexture = device->getTextures()->load("assets/container2.png");
	GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

	materialModel->setColor(diffuseTexture);
	return materialModel;
}

/// Creates boxes
void createBoxes(
	gltut::Engine& engine,
	gltut::Material* material)
{
	const int COUNT = 5;
	const float GEOMETRY_SIZE = 5.0f;
	const float STRIDE = 15.0f;
	auto* boxGeometry = engine.getFactory()->getGeometry()->createBox(gltut::Vector3(GEOMETRY_SIZE));
	GLTUT_CHECK(boxGeometry, "Failed to create geometry");

	gltut::Rng rng;
	for (int i = 0; i < COUNT; ++i)
	{
		for (int j = 0; j < COUNT; ++j)
		{
			const gltut::Vector3 size(
				rng.nextFloat(0.5f, 2.0f),
				rng.nextFloat(0.5f, 2.0f),
				rng.nextFloat(0.5f, 2.0f));

			const gltut::Vector3 position(
				(i - (COUNT - 1.0f) * 0.5f + rng.nextFloat(-0.25f, 0.25f)) * STRIDE,
				0.25f * size.y,
				(j - (COUNT - 1.0f) * 0.5f + rng.nextFloat(-0.25f, 0.25f)) * STRIDE);

			auto* object = engine.getScene()->createGeometry(
				boxGeometry,
				material,
				gltut::Matrix4::transformMatrix(
					position,
					gltut::Vector3(
						rng.nextFloat(0.0f, gltut::PI * 2.0),
						rng.nextFloat(0.0f, gltut::PI * 2.0),
						rng.nextFloat(0.0f, gltut::PI * 2.0)),
					size));

			GLTUT_CHECK(object, "Failed to create object");
		}
	}
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
		engine->getWindow()->setTitle("Water");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		gltut::Camera* camera = engine->getScene()->createCamera(
			{0.0f, 10.0f, 100.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			45.0f,
			1.0f,
			2000.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera, 0.2f, 100.0f, 1.0f, 1000.0f));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		auto* scene = engine->getScene();
		auto* factory = engine->getFactory();
		auto* geometry = factory->getGeometry()->createBox(gltut::Vector3(1.0f));
		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

		// Create framebuffer
		gltut::Texture2* colorTexture = factory->getTexture()->createWindowSizeTexture(
			gltut::TextureFormat::RGBA);
		GLTUT_CHECK(colorTexture != nullptr, "Failed to create color texture");

		gltut::Texture2* depthTexture = factory->getTexture()->createWindowSizeTexture(
			gltut::TextureFormat::FLOAT);
		GLTUT_CHECK(depthTexture != nullptr, "Failed to create depth texture");

		auto* framebuffer = engine->getRenderer()->getDevice()->getFramebuffers()->create(
			colorTexture,
			depthTexture);

		GLTUT_CHECK(framebuffer, "Failed to create framebuffer");
		engine->getSceneRenderPass()->setTarget(framebuffer);

		gltut::PhongShaderModel* phongShader = factory->getMaterial()->createPhongShader(1, 0, 0);
		gltut::FlatColorMaterialModel* materialModel = createMaterialModel(
			engine.get(),
			phongShader);
		createBoxes(*engine, materialModel->getMaterial());
		
		gltut::TextureCubemap* skyboxTexture = engine->getDevice()->getTextures()->load(
			"assets/skybox/negx.jpg",
			"assets/skybox/posx.jpg",
			"assets/skybox/negy.jpg",
			"assets/skybox/posy.jpg",
			"assets/skybox/negz.jpg",
			"assets/skybox/posz.jpg",
			gltut::TextureParameters(
				gltut::TextureFilterMode::LINEAR,
				gltut::TextureFilterMode::LINEAR,
				gltut::TextureWrapMode::CLAMP_TO_EDGE));

		const bool skyboxCreated = factory->getScene()->createSkybox(
			skyboxTexture,
			scene->getActiveCameraViewpoint(),
			nullptr,
			framebuffer);
		GLTUT_CHECK(skyboxCreated, "Failed to create skybox");

		auto* waterMaterial = createWaterMaterial(
			engine->getRenderer(),
			skyboxTexture,
			colorTexture,
			depthTexture);

		auto* waterPlaneMesh = engine->getFactory()->getGeometry()->createPlane(
			{2000.0f, 2000.0f},
			{400, 400},
			{false, false, false});

		GLTUT_CHECK(waterPlaneMesh != nullptr, "Failed to create water plane geometry");

		auto* waterGeometry = engine->getScene()->createGeometry(
			waterPlaneMesh,
			waterMaterial,
			gltut::Matrix4::rotationMatrix({gltut::toRadians(-90.0f), 0.0f, 0.0f}));
		GLTUT_CHECK(waterGeometry != nullptr, "Failed to create water geometry node");

		auto* waterColorTexture = factory->getTexture()->createWindowSizeTexture(gltut::TextureFormat::RGBA);
		auto* waterDepthTexture = factory->getTexture()->createWindowSizeTexture(gltut::TextureFormat::FLOAT);	
		auto* waterFamebuffer = engine->getRenderer()->getDevice()->getFramebuffers()->create(
			waterColorTexture,
			waterDepthTexture);

		gltut::Color clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		engine->getRenderer()->createPass(
			scene->getActiveCameraViewpoint(),
			waterGeometry->getGeometry(),
			waterFamebuffer,
			1,
			&clearColor,
			true, // Depth clearing
			nullptr);

		const char* samplerNames[] = {"colorSampler", "depthSampler", "waterColorSampler", "waterDepthSampler"};
		std::array<const gltut::Texture2*, 4> textures = {colorTexture, depthTexture, waterColorTexture, waterDepthTexture};
		gltut::RenderPass* textureToWindowPass = engine->getFactory()->getRenderPass()->createTexturesToWindowRenderPass(
			textures.data(),
			static_cast<gltut::u32>(textures.size()),
			nullptr,
			TEXTURE_TO_WINDOW_FRAGMENT_SHADER,
			samplerNames);
		GLTUT_CHECK(textureToWindowPass != nullptr, "Failed to create texture to window pass");

		auto start = std::chrono::high_resolution_clock::now();

		gltut::Color deepWaterColor(float(21) / 255, float(51) / 255, float(70) / 255);
		float deepWaterDistance = 5.0f;

		auto* waterShaderArgs = waterMaterial->getPass(1)->getShaderArguments();
		waterShaderArgs->setVec3("deepWaterColor", deepWaterColor.r, deepWaterColor.g, deepWaterColor.b);
		waterShaderArgs->setFloat("deepWaterDistance", deepWaterDistance);
		waterShaderArgs->setFloat("zNear", camera->getProjection().getNearPlane());
		waterShaderArgs->setFloat("zFar", camera->getProjection().getFarPlane());

		do
		{
			auto time = std::chrono::duration<float>(
							std::chrono::high_resolution_clock::now() - start)
							.count();

			waterShaderArgs->setFloat("time", time);

			imgui->newFrame();
			ImGui::SetNextWindowPos({10, 10}, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({200, 400}, ImGuiCond_FirstUseEver);
			ImGui::Begin("Settings");
			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());

			// Water settings
			if (ImGui::ColorEdit3("Deep water color", &deepWaterColor.r))
			{
				waterShaderArgs->setVec3("deepWaterColor", deepWaterColor.r, deepWaterColor.g, deepWaterColor.b);
			}

			if (ImGui::SliderFloat("Deep water distance", &deepWaterDistance, 1.0f, 20.0f))
			{
				waterShaderArgs->setFloat("deepWaterDistance", deepWaterDistance);
			}

			// Render depth texture in ImGui
			{
				ImGui::Text("Scene depth");
				ImGui::Image(
					depthTexture->getId(),
					{512, 512},
					{0, 1},
					{1, 0});
			}

			// Render water depth texture in ImGui
			{
				ImGui::Text("Water depth");
				ImGui::Image(
					waterDepthTexture->getId(),
					{512, 512},
					{0, 1},
					{1, 0});
			}

			ImGui::End();

		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
