// Includes
#include "GeometryFactoryC.h"
#include <array>
#include <vector>
#include "engine/math/Vector3.h"

namespace gltut
{

// Local functions
namespace
{

/// Adds faces between two circles
void addFacesBetweenCircles(
	u32 circle1Offset,
	u32 circle2Offset,
	u32 circleSegmentsCount,
	std::vector<u32>& result)
{
	for (u32 index = 1; index < circleSegmentsCount; ++index)
	{
		result.push_back(circle1Offset + index);
		result.push_back(circle1Offset + index - 1);
		result.push_back(circle2Offset + index);

		result.push_back(circle2Offset + index);
		result.push_back(circle1Offset + index - 1);
		result.push_back(circle2Offset + index - 1);
	}
}

// End of the anonymous namespace
}

// Global classes
Geometry* GeometryFactoryC::createBox(float x, float y, float z) noexcept
{
	Geometry* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		x *= 0.5f;
		y *= 0.5f;
		z *= 0.5f;

		const float vertices[] =
		{
			// Front
			-x, -y,  z,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 x, -y,  z,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
			 x,  y,  z,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
			-x,  y,  z,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,

			// Back
			-x, -y, -z,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			 x, -y, -z,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			 x,  y, -z,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			-x,  y, -z,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

			// Left
			-x, -y, -z, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			-x, -y,  z, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
			-x,  y,  z, -1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
			-x,  y, -z, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

			// Right
			 x, -y, -z,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			 x, -y,  z,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
			 x,  y,  z,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
			 x,  y, -z,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

			 // Top
			 -x,  y, -z,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			  x,  y, -z,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
			  x,  y,  z,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
			 -x,  y,  z,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

			 // Bottom
			 -x, -y, -z,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			  x, -y, -z,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			  x, -y,  z,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			 -x, -y,  z,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f
		};

		u32 indices[] =
		{
			0, 1, 2, 2, 3, 0,
			5, 4, 6, 6, 4, 7,
			8, 9, 10, 10, 11, 8,
			13, 12, 14, 14, 12, 15,
			17, 16, 18, 18, 16, 19,
			20, 21, 22, 22, 23, 20
		};

		result = mRenderer.getGeometries()->create(VERTEX_FORMAT_POS3_NORM3_TEX2, 24, vertices, 36, indices);
	GLTUT_CATCH_ALL_END("Failed to create a box geometry")
	return result;
}

Geometry* GeometryFactoryC::createSphere(float radius, u32 subdivisions) noexcept
{
	Geometry* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		GLTUT_CHECK(subdivisions >= 1, "Subdivisions must be >= 1");

		using Vertex = std::array<float, 8>;

		std::vector<Vertex> vertices;
		const u32 latSubdivisions = 2 * subdivisions;
		const u32 lonSubdivisions = 4 * subdivisions;

		const float angleDelta = PI / latSubdivisions;
		for (u32 latInd = 0; latInd <= latSubdivisions; ++latInd)
		{
			float latitude = angleDelta * static_cast<float>(latInd) - 0.5f * PI;
			for (u32 lonInd = 0; lonInd <= lonSubdivisions; ++lonInd)
			{
				const float longitude = angleDelta * static_cast<float>(lonInd);
				const Vector3 normal = setDistanceAzimuthInclination({ 1.0, longitude, latitude });

				// setDistanceAzimuthInclination uses z-axis as the up vector, so
				// so we need to swap the x and z components to use y-axis as the up vector
				vertices.push_back({
					radius * normal.x,
					radius * normal.z,
					radius * normal.y,
					normal.x,
					normal.z,
					normal.y,
					static_cast<float>(lonInd) / lonSubdivisions,
					static_cast<float>(latInd) / latSubdivisions });
			}
		}

		std::vector<u32> indices;
		for (u32 latitudeIndex = 0; latitudeIndex < latSubdivisions; ++latitudeIndex)
		{
			addFacesBetweenCircles(
				latitudeIndex * (lonSubdivisions + 1),
				(latitudeIndex + 1) * (lonSubdivisions + 1),
				lonSubdivisions + 1,
				indices);
		}

		const u32 vertexCount = static_cast<u32>(vertices.size());
		result = mRenderer.getGeometries()->create(
			VERTEX_FORMAT_POS3_NORM3_TEX2,
			vertexCount,
			vertices[0].data(),
			static_cast<u32>(indices.size()),
			indices.data());

	GLTUT_CATCH_ALL_END("Failed to create a sphere geometry")
	return result;
}

// End of the namespace gltut
}
