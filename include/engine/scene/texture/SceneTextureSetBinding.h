#pragma once

// Includes
#include "engine/renderer/texture/TextureSet.h"

namespace gltut
{
// Global classes
// Forward declarations
class Scene;

/// The class represents a shader binding for scene parameters
class SceneTextureSetBinding
{
public:
	enum class Parameter
	{
		/// The shadow map texture for directional lights
		DIRECTIONAL_LIGHT_SHADOW_MAP,
		/// The shadow map texture for spot lights
		SPOT_LIGHT_SHADOW_MAP,
		/// Total number of textures
		TOTAL_COUNT
	};

	/// Returns the bound texture set
	virtual TextureSet* getTextureSet() const noexcept = 0;

	/// Sets the bound texture set
	virtual void setTextureSet(
		TextureSet* textureSet,
		bool resetParameters = false) noexcept = 0;

	/// The total number of textures
	static constexpr u32 TOTAL_PARAMETERS = static_cast<u32>(Parameter::TOTAL_COUNT);

	/**
		Binds a scene parameter to texture slots
		\param parameter The scene parameter to bind
		\param startSlot The starting texture slot to bind the textures
	*/
	virtual void bind(
		Parameter parameter,
		u32 startSlot) noexcept = 0;

	/// Unbinds a scene parameter
	virtual void unbind(Parameter parameter) noexcept = 0;

	/// Returns the start texture slot for a scene parameter, nullptr if not bound
	virtual const u32* getStartTextureSlot(Parameter parameter) const noexcept = 0;

	/// Updates the binding
	virtual void update(const Scene* scene) const noexcept = 0;
};

// End of the namespace gltut
}
