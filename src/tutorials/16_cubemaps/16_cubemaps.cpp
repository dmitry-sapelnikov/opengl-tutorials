// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "engine/Engine.h"
#include "imgui/EngineImgui.h"
#include "asset_loader/AssetLoader.h"

static const char* REFRACTION_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

void main()
{
	position = vec3(model * vec4(inPosition, 1.0));
	normal = normalMat * inNormal;
	gl_Position = projection * view * model* vec4(inPosition, 1.0);
}
)";

static const char* REFRACTION_FRAGMENT_SHADER = R"(
#version 330 core
in vec3 position;
in vec3 normal;
out vec4 outColor;

uniform samplerCube skybox;
uniform vec3 cameraPosition;

void main()
{
	vec3 I = normalize(position - cameraPosition);
	vec3 R = refract(I, normalize(normal), 1.00 / 1.33);
	outColor = texture(skybox, R);
}
)";

class MaterialFactory : public gltut::AssetMaterialFactory
{
public:
	MaterialFactory(gltut::Material* material) :
		mMaterial(material)
	{
	}

	const gltut::Material* createMaterial(
		const gltut::Texture2*,
		const gltut::Texture2*,
		const gltut::Texture2*) const noexcept override
	{
		return mMaterial;
	}

private:
	gltut::Material* mMaterial;
};

gltut::Material* createRefractiveMaterial(
	gltut::Renderer* renderer,
	gltut::TextureCubemap* skyboxTexture)
{
	gltut::Shader* refractionShader = renderer->getDevice()->getShaders()->create(
		REFRACTION_VERTEX_SHADER,
		REFRACTION_FRAGMENT_SHADER);

	refractionShader->setInt("skybox", 0);

	GLTUT_CHECK(refractionShader != nullptr, "Failed to create refraction shader");

	auto* shaderBinding = renderer->createShaderBinding(refractionShader);
	GLTUT_CHECK(shaderBinding != nullptr, "Failed to create scene shader binding");
	shaderBinding->bind(
		gltut::ShaderRendererBinding::Parameter::GEOMETRY_MATRIX,
		"model"
	);

	shaderBinding->bind(
		gltut::ShaderRendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX,
		"view");

	shaderBinding->bind(
		gltut::ShaderRendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX,
		"projection");

	shaderBinding->bind(
		gltut::ShaderRendererBinding::Parameter::GEOMETRY_NORMAL_MATRIX,
		"normalMat");

	shaderBinding->bind(
		gltut::ShaderRendererBinding::Parameter::VIEWPOINT_POSITION,
		"cameraPosition");

	gltut::Material* refractiveMaterial = renderer->createMaterial();
	GLTUT_CHECK(refractiveMaterial != nullptr, "Failed to create refractive material");

	gltut::MaterialPass* pass = refractiveMaterial->createPass(0, shaderBinding, 1);
	GLTUT_CHECK(pass != nullptr, "Failed to create material pass");
	pass->getTextures()->setTexture(skyboxTexture, 0);

	return refractiveMaterial;
}


///	The program entry point
int main()
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	gltut::AssetLoader* assetLoader = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Cubemap");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		assetLoader = gltut::createAssetLoader(engine.get());
		GLTUT_CHECK(assetLoader != nullptr, "Failed to create asset loader");

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();
		auto* geometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry")

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

		gltut::Material* refractiveMaterial = createRefractiveMaterial(renderer, skyboxTexture);
		MaterialFactory factory(refractiveMaterial);
		auto* backpack = assetLoader->loadAsset("assets/backpack/backpack.obj", &factory, false);
		GLTUT_CHECK(backpack != nullptr, "Failed to load backpack model");

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

	gltut::deleteAssetLoader(assetLoader);
	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
