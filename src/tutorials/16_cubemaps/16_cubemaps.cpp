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
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Cubemap");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

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
			200.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

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

		const bool skyboxCreated = engine->getFactory()->getScene()->createSkybox(
			skyboxTexture,
			scene->getActiveCameraViewpoint(),
			nullptr);

		GLTUT_CHECK(skyboxCreated, "Failed to create skybox");
	
		do
		{
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
