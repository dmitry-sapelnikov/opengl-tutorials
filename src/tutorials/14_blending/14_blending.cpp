// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"
#include "engine/math/Rng.h"

namespace
{
// Local constants

/// Number of quads to create
static const size_t QUAD_COUNT = 100;

/// Range for random quad positions
static const float POSITION_RANGE = 5.0f;

// End of the anonymous namespace
}

/// The program entry point
int main()
{
	try
	{
		std::unique_ptr<gltut::Engine> engine(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");

		engine->getWindow()->setTitle("Camera");
		engine->getWindow()->showFPS(true);

		auto* device = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createQuad(gltut::Vector2(1.0f, 1.0f));
		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry")

		auto* material = engine->getFactory()->getMaterial()->createFlatColorMaterial(false);
		material->setColor(device->getDevice()->getTextures()->load(
			"assets/window.png",
			gltut::TextureParameters(
				gltut::TextureFilterMode::LINEAR_MIPMAP,
				gltut::TextureFilterMode::LINEAR,
				gltut::TextureWrapMode::CLAMP_TO_EDGE)));

		material->getMaterial()->getPass(0)->setTransparent(true);
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> quads;
		for (size_t i = 0; i < QUAD_COUNT; ++i)
		{
			gltut::Vector3 position(
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE),
				0.0f,
				rng.nextFloat(-POSITION_RANGE, POSITION_RANGE));

			quads.push_back(scene->createGeometry(
				geometry,
				material->getMaterial(),
				gltut::Matrix4::translationMatrix(position),
				nullptr,
				true));
		}

		gltut::Camera* camera = engine->getScene()->createCamera(
			{0.0f, 0.0f, 20.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			45.0f,
			0.1f,
			100.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		while (engine->update())
		{
		}
	}
	GLTUT_APPLICATION_CATCH
	return 0;
}
