// Includes
#include <array>

#include "engine/core/Check.h"
#include "engine/Engine.h"
#include "imgui/EngineImgui.h"

static const char* POINT_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 inPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float pointSize;

void main()
{
	gl_Position = projection * view * model * vec4(inPosition, 1.0f);
	vec4 unitOffset = projection * view * model * vec4(inPosition + vec3(1.0f, 0.0f, 0.0f), 1.0f);
	float pixelSize = length(gl_Position.xy / gl_Position.w - unitOffset.xy / unitOffset.w);
	gl_PointSize = pointSize * pixelSize;
}
)";

static const char* POINT_FRAGMENT_SHADER = R"(
#version 330 core
out vec4 outColor;

void main()
{
	outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

static const char* TWO_SIDED_VERTEX_SHADER = R"(
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPosition, 1.0f);
	texCoord = inTexCoord;
}
)";

static const char* TWO_SIDED_FRAGMENT_SHADER = R"(
#version 330 core

in vec2 texCoord;
out vec4 outColor;

uniform sampler2D innerSideSampler;
uniform sampler2D outerSideSampler;

void main()
{
	if (gl_FrontFacing)
		outColor = texture(innerSideSampler, texCoord);
	else
		outColor = texture(outerSideSampler, texCoord);
}
)";

static const char* FRAG_COORD_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 inPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPosition, 1.0f);
}
)";

static const char* FRAG_COORD_FRAGMENT_SHADER = R"(
#version 330 core
out vec4 outColor;

void main()
{
	if(gl_FragCoord.x < 400)
		outColor = vec4(1.0, 0.0, 0.0, 1.0);
	else
		outColor = vec4(0.0, 1.0, 0.0, 1.0);
)";

///	The program entry point
int main()
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Advanced HLSL");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		auto* renderer = engine->getRenderer();
		auto* scene = engine->getScene();

		gltut::Camera* camera = engine->getScene()->createCamera(
			{ 2.0f, 2.0f, 2.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			45.0f,
			0.1f,
			200.0f);

		std::unique_ptr<gltut::CameraController> controller(
			gltut::createMouseCameraController(*camera, 0.2f, 100.0f, 0.1f));
		GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");
		engine->getScene()->addCameraController(controller.get());

		auto* geometry = engine->getFactory()->getGeometry()->createBox(gltut::Vector3(1.0f));

		GLTUT_CHECK(geometry != nullptr, "Failed to create geometry")

		gltut::ShaderRendererBinding* pointShader = gltut::createStandardShaderBinding(
			renderer,
			POINT_VERTEX_SHADER,
			POINT_FRAGMENT_SHADER);
		GLTUT_CHECK(pointShader != nullptr, "Failed to create point shader");

		gltut::Material* material = renderer->createMaterial();
		GLTUT_CHECK(material != nullptr, "Failed to create material");

		gltut::MaterialPass* materialPass0 = material->createPass(0, pointShader, 0, 0);
		GLTUT_CHECK(materialPass0 != nullptr, "Failed to create material pass");
		materialPass0->setFaceCulling(gltut::FaceCullingMode::NONE);
		materialPass0->setPolygonFill(gltut::PolygonFillMode::POINT, 1.0, true);

		gltut::ShaderRendererBinding* twoSidedShader = gltut::createStandardShaderBinding(
			renderer,
			TWO_SIDED_VERTEX_SHADER,
			TWO_SIDED_FRAGMENT_SHADER);

		twoSidedShader->getTarget()->setInt("innerSideSampler", 0);
		twoSidedShader->getTarget()->setInt("outerSideSampler", 1);

		GLTUT_CHECK(twoSidedShader != nullptr, "Failed to create two-sided shader");
		gltut::MaterialPass* materialPass1 = material->createPass(1, twoSidedShader, 2, 0);
		GLTUT_CHECK(materialPass1 != nullptr, "Failed to create material pass");
		materialPass1->setFaceCulling(gltut::FaceCullingMode::NONE);

		materialPass1->getTextures()->setTexture(
			renderer->getDevice()->getTextures()->load("assets/brickwall.jpg"), 0
		);

		materialPass1->getTextures()->setTexture(
			renderer->getDevice()->getTextures()->load("assets/container.jpg"), 1
		);

		gltut::ShaderRendererBinding* fragCoordShader = gltut::createStandardShaderBinding(
			renderer,
			FRAG_COORD_VERTEX_SHADER,
			FRAG_COORD_FRAGMENT_SHADER);

		GLTUT_CHECK(fragCoordShader != nullptr, "Failed to create frag coord shader");
		gltut::MaterialPass* materialPass2 = material->createPass(2, fragCoordShader, 0, 0);
		GLTUT_CHECK(materialPass2 != nullptr, "Failed to create material pass");

		gltut::GeometryNode* box = scene->createGeometry(
			geometry,
			material,
			gltut::Matrix4::identity());
		GLTUT_CHECK(box != nullptr, "Failed to create box");

		pointShader->getTarget()->setFloat("pointSize", 10.0f);

		const char* shaderNames[] = { "Points", "Two-Sided", "FragCoord" };
		int currentShader = 0;
		engine->getSceneRenderPass()->setMaterialPass(currentShader);

		do
		{
			imgui->newFrame();
			ImGui::SetNextWindowPos({ 10, 10 }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize({ 200, 400 }, ImGuiCond_FirstUseEver);
			ImGui::Begin("Settings");
			ImGui::Text("FPS: %u", engine->getWindow()->getFPS());

			if (ImGui::Combo("Shader", &currentShader, shaderNames, 3))
				engine->getSceneRenderPass()->setMaterialPass(currentShader);

			ImGui::End();
		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
