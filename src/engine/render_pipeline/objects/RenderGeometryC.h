#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/render_pipeline/objects/RenderGeometry.h"

namespace gltut
{
//	Global classes
class RenderGeometryC final : public RenderGeometry, public NonCopyable
{
public:
	/// Constructor
	RenderGeometryC(
		const Mesh* geometry,
		const Material* material,
		const Matrix4& transform) noexcept :

		mGeometry(geometry),
		mMaterial(material),
		mTransform(transform)
	{
	}

	/// Returns the geometry mesh
	const Mesh* getGeometry() const noexcept final
	{
		return mGeometry;
	}

	/// Sets the geometry mesh
	void setGeometry(const Mesh* geometry) noexcept final
	{
		mGeometry = geometry;
	}

	/// Returns the material
	const Material* getMaterial() const noexcept final
	{
		return mMaterial;
	}

	/// Sets the material
	void setMaterial(const Material* material) noexcept final
	{
		mMaterial = material;
	}

	/// Returns the transformation matrix
	const Matrix4& getTransform() const noexcept final
	{
		return mTransform;
	}

	/// Sets the transformation matrix
	void setTransform(const Matrix4& transform) noexcept final
	{
		mTransform = transform;
	}

	/// Renders the object
	void render(u32 materialPass) const noexcept final;

private:
	/// The geometry
	const Mesh* mGeometry = nullptr;

	/// The material
	const Material* mMaterial = nullptr;

	/// The transformation matrix
	Matrix4 mTransform = Matrix4::identity();
};

// End of the namespace gltut
}
