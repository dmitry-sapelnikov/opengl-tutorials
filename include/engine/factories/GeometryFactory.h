#pragma once

// Includes
#include "engine/renderer/mesh/Mesh.h"

namespace gltut
{
// Global classes
class GeometryFactory
{
public:
	/**
		\brief Creates a box mesh with non-smooth normals

		\param width The width of the box
		\param height The height of the box
		\param depth The depth of the box

		\return The mesh if it was created successfully, nullptr otherwise

		\note The mesh is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative dimensions produce an inverted mesh
	*/
	virtual Mesh* createBox(float width, float height, float depth) noexcept = 0;

	/**
		\brief Creates a sphere mesh with smooth normals

		\param radius The radius of the sphere
		\param subdivisions The number of subdivisions for the sphere, must be greater than 0

		\return The mesh if it was created successfully, nullptr otherwise

		\note The mesh is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative radius produces an inverted mesh
	*/
	virtual Mesh* createSphere(float radius, u32 subdivisions) noexcept = 0;
};

// End of the namespace gltut
}
