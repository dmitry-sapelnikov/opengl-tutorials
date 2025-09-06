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
	FaceCullingMode getFaceCullingMode() const noexcept final
	{
		return mFaceCullingMode;
	}

	/// Sets the material face mode
	void setFaceCullingMode(FaceCullingMode mode) noexcept final
	{
		mFaceCullingMode = mode;
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
	FaceCullingMode mFaceCullingMode = FaceCullingMode::BACK;

	/// The transparency flag
	bool mTransparent = false;
};

// End of the namespace gltut
}
