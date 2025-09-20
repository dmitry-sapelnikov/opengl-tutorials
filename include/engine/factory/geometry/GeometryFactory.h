// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

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
	/// Options for geometry creation
	struct CreationOptions
	{
		// Whether to create normals
		bool normal;

		// Whether to create texture coordinates
		bool textureCoordinates;

		// Whether to create tangent and bitangent vectors
		bool tangentBitangent;

		// Constructor
		CreationOptions(
			bool normal = true,
			bool textureCoordinates = true,
			bool tangentBitangent = true) noexcept :
			normal(normal),
			textureCoordinates(textureCoordinates),
			tangentBitangent(tangentBitangent)
		{
		}
	};

	/// Virtual destructor
	virtual ~GeometryFactory() = default;

	/**
		\brief Creates a XY quad geometry
		\param size The size of the quad
		\param options The creation options

		\return The geometry if it was created successfully, nullptr otherwise
		\note The quad is created in the XY plane, with normal pointing in the +Z direction
	*/
	virtual Geometry* createQuad(
		const Vector2& size,
		const CreationOptions& options = {}) noexcept = 0;

	/**
		\brief Creates a box geometry with non-smooth normals
		\param size The size of the box
		\param options The creation options

		\return The geometry if it was created successfully, nullptr otherwise
		\note Negative dimensions produce an inverted geometry
	*/
	virtual Geometry* createBox(
		const Vector3& size,
		const CreationOptions& options = {}) noexcept = 0;

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
