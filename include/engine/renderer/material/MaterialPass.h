// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/RenderModes.h"
#include "engine/graphics/shader/ShaderParameters.h"
#include "engine/graphics/texture/Texture.h"
#include "engine/renderer/shader/ShaderRendererBinding.h"
#include "engine/renderer/shader/ShaderUniformBufferSet.h"
#include "engine/renderer/texture/TextureSet.h"

namespace gltut
{

// Global classes
/// The class represents a material for a single render pass
class MaterialPass
{
public:
	/// Virtual destructor
	virtual ~MaterialPass() noexcept = default;

	/// Returns the shader
	virtual const ShaderRendererBinding* getShader() const noexcept = 0;

	/// Sets the shader
	virtual void setShader(const ShaderRendererBinding* shader) noexcept = 0;

	/// Returns the shader arguments object, i.e. values of shader parameters
	virtual ShaderParameters* getShaderArguments() noexcept = 0;

	/// Returns the textures associated with this material pass
	virtual TextureSet* getTextures() noexcept = 0;

	/// Returns the uniform buffers associated with this material pass
	virtual ShaderUniformBufferSet* getShaderUniformBuffers() noexcept = 0;

	/// Returns the material cull mode
	virtual FaceCullingMode getFaceCulling() const noexcept = 0;

	/// Sets the material cull mode
	virtual void setFaceCulling(FaceCullingMode mode) noexcept = 0;

	/// Returns the transparency flag
	virtual bool isTransparent() const noexcept = 0;

	/// Sets the transparency flag
	virtual void setTransparent(bool transparent) noexcept = 0;

	/**
		\brief Sets the polygon fill mode

		\param mode The polygon fill mode

		\param size The size of the polygon outline.
		Used only if mode is PolygonFillMode::LINE or PolygonFillMode::POINT

		\param enableSizeInShader If true, the size parameter is passed to the shader.
		Used only if mode is PolygonFillMode::POINT
	*/
	virtual void setPolygonFill(
		PolygonFillMode mode,
		float size = 1.0f,
		bool enableSizeInShader = false) noexcept = 0;

	/// Binds the material pass for a render geometry
	virtual void bind(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
