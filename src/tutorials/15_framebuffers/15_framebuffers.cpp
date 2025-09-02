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
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			gltut::Vector3 position(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));

			gltut::Vector3 rotation = rng.nextFloat(0, gltut::PI * 2.0f) * 
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

		/*std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());*/

		gltut::Color clearColor(0.5f, 0.5f, 0.5f);
		engine->getSceneRenderPass()->setClearColor(&clearColor);

		//engine->getRenderer()->removeAllPasses();
		//const gltut::Point2u textureSize = engine->getWindow()->getSize();
		//auto* colorTexture = renderer->getDevice()->getTextures()->create(
		//	nullptr,
		//	textureSize,
		//	gltut::TextureFormat::RGBA,
		//	{ gltut::TextureFilterMode::NEAREST,
		//	gltut::TextureFilterMode::NEAREST,
		//	gltut::TextureWrapMode::CLAMP_TO_EDGE });

		//GLTUT_CHECK(colorTexture != nullptr, "Failed to create color texture");

		//auto* depthTexture = renderer->getDevice()->getTextures()->create(
		//	nullptr,
		//	textureSize,
		//	gltut::TextureFormat::FLOAT,
		//	{ gltut::TextureFilterMode::NEAREST,
		//	gltut::TextureFilterMode::NEAREST,
		//	gltut::TextureWrapMode::CLAMP_TO_EDGE });

		//engine->getFactory()->getTexture()->createWindowSizeTextureBinding(colorTexture);
		//engine->getFactory()->getTexture()->createWindowSizeTextureBinding(depthTexture);

		//auto* framebuffer = renderer->getDevice()->getFramebuffers()->create(
		//	colorTexture,
		//	depthTexture);
		//GLTUT_CHECK(framebuffer, "Failed to create framebuffer");

		//auto* renderToTexturePass = renderer->createPass(
		//	scene->getActiveCameraViewpoint(),
		//	scene->getRenderGroup(),
		//	framebuffer,
		//	0,
		//	&clearColor,
		//	true, // Depth clearing
		//	nullptr,
		//	true,
		//	false);

		//GLTUT_CHECK(renderToTexturePass != nullptr, "Failed to create render to texture pass");

		//auto* textureToWindowPass = engine->getFactory()->getRenderPass()->createTextureToWindowRenderPass(
		//	colorTexture,
		//	nullptr);

		do
		{
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	return 0;
}
