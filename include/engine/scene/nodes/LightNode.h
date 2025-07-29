#pragma once

// Includes
#include "engine/math/Color.h"
#include "engine/scene/nodes/SceneNode.h"

namespace gltut
{

// Global classes
/// Contains the colors used for a light source
class LightNode : public SceneNode
{
public:
	/// Type of the light source
	enum class Type
	{
		/// Directional light
		DIRECTIONAL,
		/// Point light
		POINT,
		/// Spot light
		SPOT
	};

	/// Default ambient color
	static constexpr Color DEFAULT_AMBIENT { 0.1f, 0.1f, 0.1f, 1.0f };

	/// Default diffuse color
	static constexpr Color DEFAULT_DIFFUSE { 1.0f, 1.0f, 1.0f, 1.0f };

	/// Default specular color
	static constexpr Color DEFAULT_SPECULAR { 1.0f, 1.0f, 1.0f, 1.0f };

	/// Default light direction
	static constexpr Vector3 DEFAULT_DIRECTION { 0.0f, -1.0f, 0.0f };

	/// Virtual destructor
	virtual ~LightNode() noexcept = default;

	/// Returns the type of the light
	virtual Type getType() const noexcept = 0;

	/// Sets the type of the light
	virtual void setType(Type type) noexcept = 0;

	/// Returns the light direction in the local space
	virtual const Vector3& getDirection() const noexcept = 0;

	/**
		\brief Sets the light direction in the local space.
		Normalizes the direction vector.
		If the direction vector is zero, it will be set to DEFAULT_DIRECTION
	*/
	virtual void setDirection(const Vector3& direction) noexcept = 0;

	/// Returns the light direction in the global space
	virtual Vector3 getGlobalDirection() const noexcept = 0;

	/**
		\brief Sets the light target in the parent space.
		Recomputes the direction vector.
		If the target is the same as the light position,
		it is set to DEFAULT_DIRECTION.
	*/
	virtual void setTarget(const Vector3& target) noexcept = 0;

	/// Returns the ambient color of the light
	virtual const Color& getAmbient() const noexcept = 0;

	/// Sets the ambient color of the light
	virtual void setAmbient(const Color& color) noexcept = 0;

	/// Returns the diffuse color of the light
	virtual const Color& getDiffuse() const noexcept = 0;

	/// Sets the diffuse color of the light
	virtual void setDiffuse(const Color& color) noexcept = 0;

	/// Returns the specular color of the light
	virtual const Color& getSpecular() const noexcept = 0;

	/// Sets the specular color of the light
	virtual void setSpecular(const Color& color) noexcept = 0;
};

// End of the namespace gltut
}
