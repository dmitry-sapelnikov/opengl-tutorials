// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/geometry/GeometryFactory.h"
#include "engine/factory/render_pass/RenderPassFactory.h"
#include <array>

namespace gltut
{

class RenderPassFactoryC : public RenderPassFactory, public NonCopyable
{
public:
	/// Constructor
	explicit RenderPassFactoryC(Renderer& renderer) noexcept :
		mRenderer(renderer)
	{
		mShaders.fill(nullptr);
	}

	/// Creates a texture-to-window render pass
	RenderPass* createTextureToWindowRenderPass(
		const Texture2* texture,
		const Rectangle2u* viewport) noexcept final;

	/// Creates a textures-to-window render pass
	RenderPass* createTexturesToWindowRenderPass(
		const Texture2** textures,
		u32 textureCount,
		const Rectangle2u* viewport,
		const char* fragmentShader,
		const char** textureSamplerNames) noexcept final;

private:
	/// Helper method to create render pasess
	RenderPass* createTexturesToWindowRenderPass(
		const Rectangle2u* viewport,
		Shader* shader,
		const Texture2** textures,
		u32 texturesCount);

	/// The render pipeline
	Renderer& mRenderer;

	/// Depth texture shader
	std::array<ShaderRendererBinding*, static_cast<size_t>(TextureFormat::TOTAL_COUNT)> mShaders;

	/// Render quad for the texture
	Geometry* mRenderQuad = nullptr;
};

// End of the namespace gltut
}
