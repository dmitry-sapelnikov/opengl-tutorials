// Includes
#include "engine/MeshCreation.h"
#include <array>
#include <vector>

namespace gltut
{

// Local functions
namespace
{

void addFacesBetweenCircles(
	u32 circle1Offset,
	u32 circle2Offset,
	u32 circleSegmentsCount,
	std::vector<u32>& result)
{
	u32 prevIndex = circleSegmentsCount - 1;
	for (u32 index = 0; index < circleSegmentsCount; ++index)
	{
		result.push_back(circle1Offset + prevIndex);
		result.push_back(circle1Offset + index);
		result.push_back(circle2Offset + index);

		result.push_back(circle2Offset + index);
		result.push_back(circle2Offset + prevIndex);
		result.push_back(circle1Offset + prevIndex);

		prevIndex = index;
	}
}

void addFacesBetweenPointAndCircle(
	u32 pointOffset,
	u32 circleOffset,
	u32 circleSegmentsCount,
	bool flipNormals,
	std::vector<u32>& result)
{
	u32 prevIndex = circleSegmentsCount - 1;
	for (u32 index = 0; index < circleSegmentsCount; ++index)
	{
		if (flipNormals)
		{
			result.push_back(circleOffset + index);
			result.push_back(circleOffset + prevIndex);
			result.push_back(pointOffset);
		}
		else
		{
			result.push_back(circleOffset + prevIndex);
			result.push_back(circleOffset + index);
			result.push_back(pointOffset);
		}
		prevIndex = index;
	}
}
// End of the anonymous namespace
}

// Global functions
Mesh* createBoxMesh(Scene& scene, float x, float y, float z) noexcept
{
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
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};

		return scene.createMesh(VERTEX_FORMAT_POS3_NORM3_TEX2, 24, vertices, 36, indices);
	GLTUT_CATCH_ALL_END("Failed to create a box mesh")
	return nullptr;
}

Mesh* createSphereMesh(Scene& scene, float radius, u32 subdivisions) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		GLTUT_CHECK(subdivisions >= 1, "Subdivisions must be >= 1");

		using Vertex = std::array<float, 8>;

		std::vector<Vertex> vertices;
		vertices.push_back({ 0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.0f });

		const u32 latSubdivisions = 2 * subdivisions;
		const u32 lonSubdivisions = 4 * subdivisions;

		const float angleDelta = PI / latSubdivisions;
		for (u32 latInd = 1; latInd < latSubdivisions; ++latInd)
		{
			float latitude = angleDelta * static_cast<float>(latInd) - 0.5f * PI;
			for (u32 lonInd = 0; lonInd < lonSubdivisions; ++lonInd)
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
		vertices.push_back({ 0.0f, radius, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f });

		std::vector<u32> indices;
		for (u32 latitudeIndex = 0; latitudeIndex < latSubdivisions - 2; ++latitudeIndex)
		{
			addFacesBetweenCircles(latitudeIndex * lonSubdivisions + 1, (latitudeIndex + 1) * lonSubdivisions + 1, lonSubdivisions, indices);
		}

		const u32 vertexCount = static_cast<u32>(vertices.size());
		addFacesBetweenPointAndCircle(0, 1, lonSubdivisions, true, indices);
		addFacesBetweenPointAndCircle(vertexCount - 1, vertexCount - 1 - lonSubdivisions, lonSubdivisions, false, indices);

		return scene.createMesh(
			VERTEX_FORMAT_POS3_NORM3_TEX2,
			vertexCount,
			vertices[0].data(),
			static_cast<u32>(indices.size()),
			indices.data());

	GLTUT_CATCH_ALL_END("Failed to create a sphere mesh")
	return nullptr;
}

// End of the namespace gltut
}
