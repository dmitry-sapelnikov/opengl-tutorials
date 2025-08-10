#pragma once

// Includes
#include "engine/scene/nodes/LightNode.h"
#include "./SceneNodeT.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class LightNodeC final : public SceneNodeT<LightNode>
{
public:
	LightNodeC(
		LightNode::Type type,
		const Matrix4& transform,
		SceneNode* parent) noexcept :
		SceneNodeT<LightNode>(transform, parent),
		mType(type)
	{
	}

	/// Returns the light type
	Type getType() const noexcept final
	{
		return mType;
	}

	/// Sets the light type
	void setType(Type type) noexcept final
	{
		mType = type;
	}

	/// Returns the light direction in the local frame
	const Vector3& getDirection() const noexcept final
	{
		return mDirection;
	}

	/// Return the light direction in the global frame
	Vector3 getGlobalDirection() const noexcept final
	{
		return (getGlobalTransform().getMatrix3() * mDirection).getNormalized();
	}

	/// Sets the light direction in the local frame
	void setDirection(const Vector3& direction) noexcept final
	{
		mDirection = direction.isNearZero() ?
			DEFAULT_DIRECTION :
			direction.getNormalized();
	}

	/**
		\brief Sets the light target in the parent space.
		Recomputes the direction vector.
		If the target is the same as the light position,
		it is set to DEFAULT_DIRECTION.
	*/
	void setTarget(const Vector3& target) noexcept final
	{
		const Matrix4& t = getTransform();
		setDirection(
			t.getMatrix3().getTranspose() * 
			(target - t.getTranslation()));
	}

	/// Returns the outer angle for spot lights, in radians
	float getOuterAngle() const noexcept final
	{
		return mOuterAngle;
	}

	/// Sets the outer cut-off angle, in radians.
	void setOuterAngle(float angleRadians) noexcept final
	{
		mOuterAngle = clamp(angleRadians, 0.0f, PI);
		mInnerAngle = clamp(mInnerAngle, 0.0f, mOuterAngle);
	}

	/// Returns the inner angle for spot lights, in radians
	float getInnerAngle() const noexcept final
	{
		return mInnerAngle;
	}

	/// Sets the inner cut-off angle, in radians.
	void setInnerAngle(float angleRadians) noexcept final
	{
		mInnerAngle = clamp(angleRadians, 0.0f, mOuterAngle);
	}

	/// Returns the linear attenuation for point and spot lights
	float getLinearAttenuation() const noexcept final
	{
		return mLinearAttenuation;
	}

	/// Sets the linear attenuation for point and spot lights
	void setLinearAttenuation(float linearAttenuation) noexcept final
	{
		mLinearAttenuation = linearAttenuation;
	}

	/// Returns the quadratic attenuation for point and spot lights
	float getQuadraticAttenuation() const noexcept final
	{
		return mQuadraticAttenuation;
	}

	/// Sets the quadratic attenuation for point and spot lights
	void setQuadraticAttenuation(float quadraticAttenuation) noexcept final
	{
		mQuadraticAttenuation = quadraticAttenuation;
	}

	/// Returns the ambient color
	const Color& getAmbient() const noexcept final
	{
		return mAmbient;
	}

	/// Sets the ambient color
	void setAmbient(const Color& ambient) noexcept final
	{
		mAmbient = ambient;
	}

	/// Returns the diffuse color
	const Color& getDiffuse() const noexcept final
	{
		return mDiffuse;
	}

	/// Sets the diffuse color
	void setDiffuse(const Color& diffuse) noexcept final
	{
		mDiffuse = diffuse;
	}

	/// Returns the specular color
	const Color& getSpecular() const noexcept final
	{
		return mSpecular;
	}

	/// Sets the specular color
	void setSpecular(const Color& specular) noexcept final
	{
		mSpecular = specular;
	}

	/// Returns the shadow map
	ShadowMap* getShadowMap() const noexcept final
	{
		return mShadowMap;
	}

	/// Sets the shadow map`
	void setShadowMap(ShadowMap* shadowMap) noexcept final
	{
		mShadowMap = shadowMap;
	}

private:
	/// The light type
	LightNode::Type mType;

	/// The light direction
	Vector3 mDirection{ DEFAULT_DIRECTION };

	/// The inner angle for spot lights, in radians
	float mInnerAngle = PI * 0.5f;

	/// The outer angle for spot lights, in radians
	float mOuterAngle = PI * 0.5f;
	
	/// Linear attenuation for point and spot lights
	float mLinearAttenuation{ 0.0f };

	/// Quadratic attenuation for point and spot lights
	float mQuadraticAttenuation{ 0.0f };

	/// The ambient color
	Color mAmbient{ DEFAULT_AMBIENT };

	/// The diffuse color
	Color mDiffuse{ DEFAULT_DIFFUSE };

	/// The specular color
	Color mSpecular{ DEFAULT_SPECULAR };

	/// The shadow map
	ShadowMap* mShadowMap = nullptr;
};

// End of the namespace gltut
}
