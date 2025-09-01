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
	gltut::EngineImgui* imgui = nullptr;
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

		gltut::Shader* shader = renderer->getDevice()->getShaders()->load(
			"assets/shader.vs",
			"assets/shader.fs");

		GLTUT_CHECK(shader != 0, "Failed to create shader program")
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);

		auto* materialBinding = renderer->createShaderBinding(shader);
		GLTUT_CHECK(materialBinding, "Failed to create light shader material binding");
		materialBinding->bind(
			gltut::ShaderRendererBinding::Parameter::GEOMETRY_MATRIX,
			"model");

		materialBinding->bind(
			gltut::ShaderRendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX,
			"view");

		materialBinding->bind(
			gltut::ShaderRendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX,
			"projection");

		gltut::Texture* texture1 = renderer->getDevice()->getTextures()->load("assets/container.jpg", {});
		GLTUT_CHECK(texture1 != nullptr, "Failed to load texture");

		gltut::Texture* texture2 = renderer->getDevice()->getTextures()->load("assets/awesomeface.png");
		GLTUT_CHECK(texture2 != nullptr, "Failed to load texture");

		auto* material = renderer->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		auto* materialPass = material->createPass(0, materialBinding, 2);
		GLTUT_CHECK(materialPass != nullptr, "Failed to create material pass");

		materialPass->getTextures()->setTexture(texture1, 0);
		materialPass->getTextures()->setTexture(texture2, 1);

		gltut::Rng rng;
		std::vector<gltut::GeometryNode*> boxes;
		std::vector<gltut::Vector3> boxPositions;
		for (size_t i = 0; i < BOX_COUNT; ++i)
		{
			boxes.push_back(scene->createGeometry(geometry, material));
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

		// Create deferred rendering
		engine->getRenderer()->removeAllPasses();
		gltut::Color clearColor{ 0.5f, 0.5f, 0.5f };
		renderer->createPass(
			nullptr,
			nullptr,
			renderer->getDevice()->getFramebuffers()->getDefault(),
			0,
			&clearColor,
			true,
			nullptr);

		gltut::Texture* rgbaTexture = renderer->getDevice()->getTextures()->create(
			nullptr,
			{ 512, 512 },
			gltut::TextureFormat::RGB);

		gltut::Texture* depthTexture = renderer->getDevice()->getTextures()->create(
			nullptr,
			{ 512, 512 },
			gltut::TextureFormat::FLOAT);

		GLTUT_CHECK(rgbaTexture != nullptr, "Failed to create RGBA texture");

		auto* framebuffer = renderer->getDevice()->getFramebuffers()->create(
			rgbaTexture,
			depthTexture);

		gltut::Color redColor{ 1.0f, 0.0f, 0.0f, 1.0f };
		auto pass = renderer->createPass(
			scene->getActiveCameraViewpoint(),
			scene->getRenderGroup(),
			framebuffer,
			0,
			&redColor,
			true,
			nullptr);

		renderer->setPassPriority(pass, -1);

		//engine->getFactory()->getRenderPass()->createTextureToWindowRenderPass(
		//	rgbaTexture,
		//	1,
		//	nullptr);

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui instance");

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

			imgui->newFrame();
			ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({ 200, 400 }, ImGuiCond_FirstUseEver);

			ImGui::Begin("Settings");

			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());
			ImGui::Text("Time: %.2f seconds", time);

			// Plot the render texture
			if (rgbaTexture != nullptr)
			{
				ImGui::Text("Render texture");
				ImGui::Image(
					depthTexture->getId(),
					{ 200, 200 },
					{ 0, 1 }, { 1, 0 });
			}

			ImGui::End();
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	return 0;
}
