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

///	The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");

		engine->getWindow()->setTitle("Camera");
		engine->getWindow()->showFPS(true);

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry")

		auto* material = engine->getFactory()->getMaterial()->createFlatColorMaterial(true);
		material->setColor(
			renderer->getDevice()->getTextures()->load("assets/container.jpg", {}));

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> boxes;
		std::vector<gltut::Vector3> boxPositions;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			boxes.push_back(scene->createGeometry(geometry, material->getMaterial()));
			boxPositions.emplace_back(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));
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


		engine->getRenderer()->removeAllPasses();
		const gltut::u32 textureSize = 512;
		auto* colorTexture = renderer->getDevice()->getTextures()->create(
			nullptr,
			{ textureSize, textureSize },
			gltut::TextureFormat::RGBA,
			{ gltut::TextureFilterMode::NEAREST,
			gltut::TextureFilterMode::NEAREST,
			gltut::TextureWrapMode::CLAMP_TO_EDGE });

		GLTUT_CHECK(colorTexture != nullptr, "Failed to create color texture");

		auto* depthTexture = renderer->getDevice()->getTextures()->create(
			nullptr,
			{ textureSize, textureSize },
			gltut::TextureFormat::FLOAT,
			{ gltut::TextureFilterMode::NEAREST,
			gltut::TextureFilterMode::NEAREST,
			gltut::TextureWrapMode::CLAMP_TO_EDGE });

		auto* framebuffer = renderer->getDevice()->getFramebuffers()->create(
			colorTexture,
			depthTexture);
		GLTUT_CHECK(framebuffer, "Failed to create framebuffer");

		gltut::Color clearColor(0.5f, 0.5f, 0.5f);
		auto* renderToTexturePass = renderer->createPass(
			scene->getActiveCameraViewpoint(),
			scene->getRenderGroup(),
			framebuffer,
			0,
			&clearColor,
			true, // Depth clearing
			nullptr,
			true,
			false);

		GLTUT_CHECK(renderToTexturePass != nullptr, "Failed to create shadow map render pass");
		renderer->setPassPriority(renderToTexturePass, 0);

		auto* textureToWindowPass = engine->getFactory()->getRenderPass()->createTextureToWindowRenderPass(
			colorTexture,
			nullptr);
		renderer->setPassPriority(textureToWindowPass, 1000);

		auto start = std::chrono::high_resolution_clock::now();
		do
		{
			auto now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float>(now - start).count();
			auto rotation = gltut::Matrix4::rotationMatrix({ time, time, time });

			for (size_t i = 0; i < BOX_COUNT; ++i)
			{
				boxes[i]->setTransform(
					gltut::Matrix4::translationMatrix(boxPositions[i]) * rotation);
			}
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	return 0;
}
