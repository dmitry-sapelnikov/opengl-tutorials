#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/material/MaterialPass.h"
#include "../../graphics/shader/ShaderArguments.h"
#include "../texture/TextureSetC.h"

namespace gltut
{

class MaterialPassC final : public MaterialPass, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialPassC(
		GraphicsDevice& device,
		const ShaderRendererBinding* shader,
		u32 textureSlotsCount) noexcept;

	/// Returns the shader binding
	const ShaderRendererBinding* getShader() const noexcept final;

	/// Sets the shader binding
	void setShader(const ShaderRendererBinding* shader) noexcept final;

	/// Returns the shader controller
	ShaderParameters* getShaderArguments() noexcept final
	{
		return &mShaderArguments;
	}

	/// Returns the texture associated with the specified slot
	TextureSet* getTextures() noexcept final
	{
		return &mTextures;
	}

	/// Returns the material face mode
	FaceCullingMode getFaceCulling() const noexcept final
	{
		return mFaceCulling;
	}

	/// Sets the material face mode
	void setFaceCulling(FaceCullingMode mode) noexcept final
	{
		mFaceCulling = mode;
	}

	/// Returns the transparency flag
	bool isTransparent() const noexcept final
	{
		return mTransparent;
	}

	/// Sets the transparency flag
	void setTransparent(bool transparent) noexcept final
	{
		mTransparent = transparent;
	}

	/// Sets the polygon fill mode
	void setPolygonFill(
		PolygonFillMode mode,
		float size = 1.0f,
		bool enableSizeInShader = false) noexcept
	{
		mPolygonFill = mode;
		mPolygonFillSize = size;
		mPolygonFillSizeInShader = enableSizeInShader;
	}

	/// Binds the material pass for a render geometry
	void bind(const RenderGeometry* geometry) const noexcept final;

private:
	/// The graphics device
	GraphicsDevice& mDevice;

	/// The shader binding
	const ShaderRendererBinding* mShaderBinding;

	/// The shader arguments
	ShaderArguments mShaderArguments;

	/// The textures
	TextureSetC mTextures;

	/// The face mode
	FaceCullingMode mFaceCulling = FaceCullingMode::BACK;

	/// The transparency flag
	bool mTransparent = false;

	/// The polygon fill mode
	PolygonFillMode mPolygonFill = PolygonFillMode::SOLID;

	/// The polygon fill size
	float mPolygonFillSize = 1.0f;

	/// If true, the polygon fill size is passed to the shader
	bool mPolygonFillSizeInShader = false;
};

// End of the namespace gltut
}
