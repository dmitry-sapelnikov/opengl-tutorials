#pragma once

// Includes
#include "engine/math/Vector2.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
// Global classes
/// The geometry factory interface. Creates various render geometries.
class GeometryFactory
{
public:
	/**
		\brief Creates a box geometry with non-smooth normals

		\param width The width of the box
		\param height The height of the box
		\param depth The depth of the box

		\return The geometry if it was created successfully, nullptr otherwise

		\note The geometry is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative dimensions produce an inverted geometry
	*/
	virtual Geometry* createBox(float width, float height, float depth) noexcept = 0;

	/**
		\brief Creates a sphere geometry with smooth normals

		\param radius The radius of the sphere
		\param subdivisions The number of subdivisions for the sphere, must be greater than 0

		\return The geometry if it was created successfully, nullptr otherwise

		\note The geometry is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative radius produces an inverted geometry
	*/
	virtual Geometry* createSphere(float radius, u32 subdivisions) noexcept = 0;
};

// End of the namespace gltut
}
