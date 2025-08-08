// Includes
#include "RenderPassFactoryC.h"

namespace gltut
{

/// </summary>
namespace
{
// Local constants
static const char* TEXTURE_TO_WINDOW_VERTEX_SHADER = R"(
	#version 330 core
	layout(location = 0) in vec3 inPos;
	layout(location = 1) in vec2 inTexCoord;
	out vec2 texCoord;
	void main()
	{
		gl_Position = vec4(inPos, 1.0);
		texCoord = inTexCoord;
	};
)";

const char* TEXTURE_TO_WINDOW_FRAGMENT_SHADER = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
void main()
{
	outColor = texture(textureSampler, texCoord);
})";

// Local functions
/// Creates a render quad for texture-to-window rendering
Mesh* createRenderQuad(RenderPipeline& renderer) noexcept
{
	Mesh* result = nullptr;

	GLTUT_CATCH_ALL_BEGIN
		float vertices1[] = {
					1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
					1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
					-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
					-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left 
	};

	unsigned indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	result = renderer.getRenderer()->createMesh(
		gltut::VERTEX_FORMAT_POS3_TEX2,
		4,
		vertices1,
		6,
		indices);
	GLTUT_CATCH_ALL_END("Failed to create render quad for texture-to-window");
	return result;
}
}

/// Creates a texture-to-window render pass
RenderPass* RenderPassFactoryC::createTextureToWindowRenderPass(
	const Texture* texture,
	const Rectangle2u& viewport) noexcept
{
	RenderPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		GLTUT_CHECK(texture != nullptr, "Texture must not be null");

		if (mTextureToWindowShader == nullptr)
		{
			Shader* shader = mRenderer.getRenderer()->createShader(
				TEXTURE_TO_WINDOW_VERTEX_SHADER,
				TEXTURE_TO_WINDOW_FRAGMENT_SHADER);
			GLTUT_CHECK(
				shader != nullptr,
				"Failed to create texture-to-window shader");

			shader->setInt("textureSampler", 0);

			mTextureToWindowShader = mRenderer.createShaderMaterialBinding(shader);
			GLTUT_CHECK(
				mTextureToWindowShader != nullptr,
				"Failed to create texture-to-window shader material binding");
		}

		if (mRenderQuad == nullptr)
		{
			mRenderQuad = createRenderQuad(mRenderer);
			GLTUT_CHECK(
				mRenderQuad != nullptr,
				"Failed to create render quad for texture-to-window");
		}

		// Create the render material
		Material* material = mRenderer.createMaterial();
		GLTUT_CHECK(
			material != nullptr,
			"Failed to create material for texture-to-window render pass");

		MaterialPass* materialPass = material->createPass(
			0,
			mTextureToWindowShader,
			1);

		GLTUT_CHECK(
			materialPass != nullptr,
			"Failed to create material pass for texture-to-window render pass");

		materialPass->setTexture(texture, 0);

		RenderObject* object = mRenderer.createGeometry(
			mRenderQuad,
			material,
			Matrix4::identity());

		GLTUT_CHECK(
			object != nullptr,
			"Failed to create render object for texture-to-window render pass");

		result = mRenderer.createPass(
			nullptr, // No viewpoint
			object,
			mRenderer.getRenderer()->getWindowFramebuffer(),
			0, // Material pass 0
			nullptr, // No clear color
			true, // Depth clearing
			&viewport);

	GLTUT_CATCH_ALL_END("Failed to create texture-to-window render pass");
	return result;
}

// End of the namespace gltut
}
