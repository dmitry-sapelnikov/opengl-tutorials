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

const char* TEXTURE_TO_WINDOW_FRAGMENT_SHADER_RGB = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
void main()
{
	vec3 color = texture(textureSampler, texCoord).rgb;
	outColor = vec4(color, 1.0);
})";

const char* TEXTURE_TO_WINDOW_FRAGMENT_SHADER_RGBA = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
void main()
{
	outColor = texture(textureSampler, texCoord);
})";

const char* TEXTURE_TO_WINDOW_FRAGMENT_SHADER_FLOAT = R"(
#version 330 core
in vec2 texCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
void main()
{
	float depth = texture(textureSampler, texCoord).r;
	outColor = vec4(depth, depth, depth, 1.0);
})";


// Local functions
/// Creates a texture-to-render target shader
ShaderRendererBinding* createShader(Renderer& renderer, TextureFormat format)
{
	Shader* shader = nullptr;
	switch (format)
	{
	case TextureFormat::RGB:
	{
		shader = renderer.getDevice()->getShaders()->create(
			TEXTURE_TO_WINDOW_VERTEX_SHADER,
			TEXTURE_TO_WINDOW_FRAGMENT_SHADER_RGBA);
	}
	break;

	case TextureFormat::RGBA:
	{
		shader = renderer.getDevice()->getShaders()->create(
			TEXTURE_TO_WINDOW_VERTEX_SHADER,
			TEXTURE_TO_WINDOW_FRAGMENT_SHADER_RGBA);
	}
	break;

	case TextureFormat::FLOAT:
	{
		shader = renderer.getDevice()->getShaders()->create(
			TEXTURE_TO_WINDOW_VERTEX_SHADER,
			TEXTURE_TO_WINDOW_FRAGMENT_SHADER_FLOAT);
	}
	break;

	GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(format)
	}

	GLTUT_CHECK(shader != nullptr, "Failed to create texture-to-render-target shader");
	shader->setInt("textureSampler", 0);
	return renderer.createShaderBinding(shader);
}

/// Creates a render quad for texture-to-window rendering
Geometry* createRenderQuad(Renderer& renderer) noexcept
{
	Geometry* result = nullptr;

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

	result = renderer.getDevice()->getGeometries()->create(
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
	const Rectangle2u* viewport) noexcept
{
	RenderPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		GLTUT_CHECK(texture != nullptr, "Texture must not be null");

		const size_t shaderIndex = static_cast<size_t>(texture->getFormat());
		if (mShaders[shaderIndex] == nullptr)
		{
			mShaders[shaderIndex] = createShader(mRenderer, texture->getFormat());
			GLTUT_CHECK(
				mShaders[shaderIndex] != nullptr,
				"Failed to create shader for texture-to-window render pass");
		}
		ShaderRendererBinding* shader = mShaders[shaderIndex];

		result = createTexturesToWindowRenderPass(
			viewport,
			shader->getShader(),
			&texture,
			1);
	GLTUT_CATCH_ALL_END("Failed to create texture-to-window render pass");
	return result;
}

/// Creates a textures-to-window render pass
RenderPass* RenderPassFactoryC::createTexturesToWindowRenderPass(
	const Texture** textures,
	u32 textureCount,
	const Rectangle2u* viewport,
	const char* fragmentShader,
	const char** textureSamplerNames) noexcept
{
	RenderPass* result = nullptr;
	try
	{
		GLTUT_CHECK(textures != nullptr, "Textures must not be null");
		GLTUT_CHECK(textureCount > 0, "Texture count must be greater than zero");
		GLTUT_CHECK(fragmentShader != nullptr, "Fragment shader must not be null");
		GLTUT_CHECK(textureSamplerNames != nullptr, "Texture sampler names must not be null");

		if (mRenderQuad == nullptr)
		{
			mRenderQuad = createRenderQuad(mRenderer);
			GLTUT_CHECK(
				mRenderQuad != nullptr,
				"Failed to create render quad for textures-to-window");
		}

		// Create the shader
		Shader* shader = mRenderer.getDevice()->getShaders()->create(
			TEXTURE_TO_WINDOW_VERTEX_SHADER,
			fragmentShader);

		GLTUT_CHECK(
			shader != nullptr,
			"Failed to create shader for textures-to-window render pass");

		// Set the texture samplers
		for (u32 i = 0; i < textureCount; ++i)
		{
			GLTUT_CHECK(
				textureSamplerNames[i] != nullptr,
				"Texture sampler name must not be null");
			shader->setInt(textureSamplerNames[i], static_cast<int32>(i));
		}

		result = createTexturesToWindowRenderPass(
			viewport,
			shader,
			textures,
			textureCount);
	}
	GLTUT_CATCH_ALL("Failed to create textures-to-window render pass");
	return result;
}

RenderPass* RenderPassFactoryC::createTexturesToWindowRenderPass(
	const Rectangle2u* viewport,
	Shader* shader,
	const Texture** textures,
	u32 texturesCount)
{
	GLTUT_CHECK(shader != nullptr, "Shader must not be null");
	GLTUT_CHECK(textures != nullptr, "Textures must not be null");
	GLTUT_CHECK(texturesCount > 0, "Texture count must be greater than zero");

	if (mRenderQuad == nullptr)
	{
		mRenderQuad = createRenderQuad(mRenderer);
		GLTUT_CHECK(
			mRenderQuad != nullptr,
			"Failed to create render quad for texture-to-window");
	}

	ShaderRendererBinding* shaderBinding = mRenderer.createShaderBinding(shader);
	GLTUT_CHECK(
		shaderBinding != nullptr,
		"Failed to create shader binding for textures-to-window render pass");

	// Create the render material
	Material* material = mRenderer.createMaterial();
	GLTUT_CHECK(
		material != nullptr,
		"Failed to create material for texture-to-window render pass");

	MaterialPass* materialPass = material->createPass(0, shaderBinding, texturesCount);

	GLTUT_CHECK(
		materialPass != nullptr,
		"Failed to create material pass for texture-to-window render pass");

	for (u32 i = 0; i < texturesCount; ++i)
	{
		GLTUT_CHECK(
			textures[i] != nullptr,
			"Texture must not be null");
		materialPass->getTextures()->setTexture(textures[i], i);
	}

	RenderObject* quadRenderGeometry = mRenderer.createGeometry(
		mRenderQuad,
		material,
		Matrix4::identity());

	GLTUT_CHECK(
		quadRenderGeometry != nullptr,
		"Failed to create render quadRenderGeometry for texture-to-window render pass");

	return mRenderer.createPass(
		nullptr, // No viewpoint
		quadRenderGeometry,
		mRenderer.getDevice()->getFramebuffers()->getDefault(),
		0, // Material pass 0
		nullptr, // No clear color
		true, // Depth clearing
		viewport,
		false, // No back face culling
		false // No front face culling
	);
	// TODO: add render pass without depth test
}


// End of the namespace gltut
}
