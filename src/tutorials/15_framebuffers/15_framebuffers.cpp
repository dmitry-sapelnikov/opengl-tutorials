// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"
#include "imgui/EngineImgui.h"

static const size_t BOX_COUNT = 100;
static const float POSITION_RANGE = 5.0f;

// Color inversion fragment shader
static const char* INVERT_FRAGMENT_SHADER = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;

void main()
{
	vec3 color = texture(textureSampler, texCoord).rgb;
	outColor = vec4(vec3(1.0) - color, 1.0);
})";

// Grayscale fragment shader
static const char* GRAYSCALE_FRAGMENT_SHADER = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;

void main()
{
	vec3 color = texture(textureSampler, texCoord).rgb;
	float gray = (color.r + color.g + color.b) / 3.0;
	outColor = vec4(gray, gray, gray, 1.0);
})";

// Gaussian blur fragment shader
static const char* BLUR_FRAGMENT_SHADER = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;

const float offset = 1.0 / 300.0;
const float kernel[9] = float[](
	1.0 / 16, 2.0 / 16, 1.0 / 16,
	2.0 / 16, 4.0 / 16, 2.0 / 16,
	1.0 / 16, 2.0 / 16, 1.0 / 16
);

void main()
{
	vec3 col = vec3(0.0);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			vec2 delta = vec2((i - 1) * offset, (j - 1) * offset);
			col += texture(textureSampler, texCoord + delta).rgb * kernel[i * 3 + j];
		}
	}
	outColor = vec4(col, 1.0);
})";

///	The program entry point
int main()
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Framebuffer Effects");

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry")

		auto* material = engine->getFactory()->getMaterial()->createFlatColorMaterial(true);
		material->setColor(
			renderer->getDevice()->getTextures()->load("assets/container.jpg", {}));

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> boxes;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			const gltut::Vector3 position(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));

			const gltut::Vector3 rotation = 
				rng.nextFloat(0, gltut::PI * 2.0f) *
				gltut::Vector3(
					rng.nextFloat(),
					rng.nextFloat(),
					rng.nextFloat()).normalize();

			boxes.push_back(scene->createGeometry(
				geometry,
				material->getMaterial(),
				gltut::Matrix4::transformMatrix(
					position,
					rotation,
					gltut::Vector3(1.0f))));
		}

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ 0.0f, 0.0f, 20.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			100.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		gltut::Color clearColor(0.1f, 0.1f, 0.1f);

		engine->getRenderer()->removeAllPasses();
		const gltut::Point2u textureSize = engine->getWindow()->getSize();
		auto* colorTexture = renderer->getDevice()->getTextures()->create(
			{ nullptr,
			textureSize,
			gltut::TextureFormat::RGBA },
			{ gltut::TextureFilterMode::NEAREST,
			gltut::TextureFilterMode::NEAREST,
			gltut::TextureWrapMode::CLAMP_TO_EDGE });

		GLTUT_CHECK(colorTexture != nullptr, "Failed to create color texture");

		auto* depthTexture = renderer->getDevice()->getTextures()->create(
			{ nullptr,
			textureSize,
			gltut::TextureFormat::FLOAT },
			{ gltut::TextureFilterMode::NEAREST,
			gltut::TextureFilterMode::NEAREST,
			gltut::TextureWrapMode::CLAMP_TO_EDGE });

		engine->getFactory()->getTexture()->createWindowSizeTextureBinding(colorTexture);
		engine->getFactory()->getTexture()->createWindowSizeTextureBinding(depthTexture);

		auto* framebuffer = renderer->getDevice()->getFramebuffers()->create(
			colorTexture,
			depthTexture);
		GLTUT_CHECK(framebuffer, "Failed to create framebuffer");

		auto* renderToTexturePass = renderer->createPass(
			scene->getActiveCameraViewpoint(),
			scene->getRenderGroup(),
			framebuffer,
			0,
			&clearColor,
			true, // Depth clearing
			nullptr);

		GLTUT_CHECK(renderToTexturePass, "Failed to create render to texture pass");

		const gltut::Texture2* textures[] = { colorTexture };
		const char* textureNames[] = { "textureSampler" };

		std::vector<std::pair<std::string, const char* >> effects = {
			{ "Invert", INVERT_FRAGMENT_SHADER },
			{ "Grayscale", GRAYSCALE_FRAGMENT_SHADER },
			{ "Blur", BLUR_FRAGMENT_SHADER }
		};

		std::vector<gltut::RenderPass*> effectPasses;
		for (const auto& [name, shader] : effects)
		{
			gltut::RenderPass* effectPass = engine->getFactory()->getRenderPass()->createTexturesToWindowRenderPass(
				textures,
				1,
				nullptr,
				shader,
				textureNames);
			GLTUT_CHECK(effectPass, ("Failed to create " + name + " pass").c_str());
			effectPass->setActive(false);
			effectPasses.push_back(effectPass);
		}

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		gltut::u32 currentEffect = 0;
		effectPasses[currentEffect]->setActive(true);

		do
		{
			imgui->newFrame();
			ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({ 200, 400 }, ImGuiCond_FirstUseEver);

			ImGui::Begin("Settings");
			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());

			// Dropdown to select post-processing effect
			if (ImGui::BeginCombo("Effect", effects[currentEffect].first.c_str()))
			{
				for (gltut::u32 i = 0; i < static_cast<gltut::u32>(effects.size()); ++i)
				{
					if (ImGui::Selectable(effects[i].first.c_str(), currentEffect == i))
					{
						effectPasses[currentEffect]->setActive(false);
						currentEffect = i;
						effectPasses[currentEffect]->setActive(true);
					}
				}
				ImGui::EndCombo();
			}
			ImGui::End();
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
