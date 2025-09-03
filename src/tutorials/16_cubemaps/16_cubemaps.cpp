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

static const char* CUBEMAP_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 position;
out vec3 TexCoords;
uniform mat4 projection;
uniform mat4 view;
void main()
{
	TexCoords = position;
	vec4 pos = view * vec4(position, 0.0);
	pos = projection * vec4(pos.xyz, 1.0);
	// A trick to set depth to 1.0
	gl_Position = pos.xyww;
	gl_Position.z *= 0.9999;
})";

static const char* CUBEMAP_FRAGMENT_SHADER = R"(
#version 330 core
in vec3 TexCoords;
uniform samplerCube skyboxSampler;
out vec4 outColor;

void main()
{
	outColor = texture(skyboxSampler, TexCoords);
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

		gltut::Geometry* skyboxCube = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));
		GLTUT_CHECK(skyboxCube, "Failed to create skybox geometry");

		gltut::Shader* skyboxShader = engine->getDevice()->getShaders()->create(
			CUBEMAP_VERTEX_SHADER,
			CUBEMAP_FRAGMENT_SHADER);
		GLTUT_CHECK(skyboxShader, "Failed to create skybox shader");

		skyboxShader->setInt("skyboxSampler", 0);

		gltut::ShaderRendererBinding* skyboxShaderBinding = engine->getRenderer()->createShaderBinding(skyboxShader);
		GLTUT_CHECK(skyboxShaderBinding, "Failed to create skybox shader binding");
		skyboxShaderBinding->bind(
			gltut::ShaderRendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX,
			"view");

		skyboxShaderBinding->bind(
			gltut::ShaderRendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX,
			"projection");

		gltut::Material* skyboxMaterial = engine->getRenderer()->createMaterial();
		GLTUT_CHECK(skyboxMaterial, "Failed to create skybox material");
		skyboxMaterial->createPass(0, skyboxShaderBinding, 1);
		(*skyboxMaterial)[0]->getTextures()->setTexture(skyboxTexture, 0);

		gltut::RenderGeometry* skyboxRenderGeometry = engine->getRenderer()->createGeometry(
			skyboxCube,
			skyboxMaterial,
			{});
		GLTUT_CHECK(skyboxRenderGeometry != nullptr, "Failed to create skybox render geometry");

		gltut::RenderPass* skyboxPass = engine->getRenderer()->createPass(
			engine->getScene()->getActiveCameraViewpoint(),
			skyboxRenderGeometry,
			engine->getDevice()->getFramebuffers()->getDefault(),
			0, // Material pass
			nullptr, // No clear color
			false, // No depth clearing
			nullptr, // Full viewport
			false, false); // No face culling

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
