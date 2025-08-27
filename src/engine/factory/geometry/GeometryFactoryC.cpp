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

std::vector<std::pair<Vector3, Vector3>> getTangentBitangent(
	const Vector3* positions,
	const u32 positionsCount,
	const Vector2* textureCoordinates,
	const u32* indices,
	const u32 indexCount) noexcept
{
	GLTUT_ASSERT(positions != nullptr);
	GLTUT_ASSERT(positionsCount > 0);
	GLTUT_ASSERT(textureCoordinates != nullptr);
	GLTUT_ASSERT(indices != nullptr);
	GLTUT_ASSERT(indexCount > 0);
	GLTUT_ASSERT(indexCount % 3 == 0);

	std::vector<std::pair<Vector3, Vector3>> result(positionsCount);
	// Iterate for each triangle
	for (u32 i = 0; i < indexCount / 3; ++i)
	{
		u32 inds[3];
		for (u32 j = 0; j < 3; ++j)
		{
			inds[j] = indices[i * 3 + j];
			GLTUT_ASSERT(inds[j] < positionsCount);
		}

		Vector3 tangent;
		Vector3 bitangent;
		getTangentSpace(
			positions[inds[0]],
			positions[inds[1]],
			positions[inds[2]],
			textureCoordinates[inds[0]],
			textureCoordinates[inds[1]],
			textureCoordinates[inds[2]],
			tangent,
			bitangent);

		for (u32 j = 0; j < 3; ++j)
		{
			result[inds[j]].first += tangent;
			result[inds[j]].second += bitangent;
		}
	}

	for (auto& tb : result)
	{
		tb.first.normalize();
		tb.second.normalize();
	}
	return result;
}

// End of the anonymous namespace
}

// Global classes

Geometry* GeometryFactoryC::createBox(
	const Vector3& size,
	const CreationOptions& options) noexcept
{
	static constexpr Vector3 normals[] =
	{
		// Front
		{ 0.0f, 0.0f,  1.0f },
		{ 0.0f, 0.0f,  1.0f },
		{ 0.0f, 0.0f,  1.0f },
		{ 0.0f, 0.0f,  1.0f },

		// Back
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },

		// Left
		{ -1.0f, 0.0f,  0.0f },
		{ -1.0f, 0.0f,  0.0f },
		{ -1.0f, 0.0f,  0.0f },
		{ -1.0f, 0.0f,  0.0f },

		// Right
		{ 1.0f, 0.0f,  0.0f },
		{ 1.0f, 0.0f,  0.0f },
		{ 1.0f, 0.0f,  0.0f },
		{ 1.0f, 0.0f,  0.0f },

		// Top
	   { 0.0f, 1.0f,  0.0f },
	   { 0.0f, 1.0f,  0.0f },
	   { 0.0f, 1.0f,  0.0f },
	   { 0.0f, 1.0f,  0.0f },

	   // Bottom
	  { 0.0f, -1.0f, 0.0f },
	  { 0.0f, -1.0f, 0.0f },
	  { 0.0f, -1.0f, 0.0f },
	  { 0.0f, -1.0f, 0.0f }
	};

	static constexpr Vector2 textureCoordinates[] =
	{
		// Front
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		// Back
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		// Left
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		// Right
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		// Top
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		// Bottom
	   { 0.0f, 0.0f },
	   { 1.0f, 0.0f },
	   { 1.0f, 1.0f },
	   { 0.0f, 1.0f }
	};

	static constexpr u32 indices[] =
	{
		0, 1, 2, 2, 3, 0,
		5, 4, 6, 6, 4, 7,
		8, 9, 10, 10, 11, 8,
		13, 12, 14, 14, 12, 15,
		17, 16, 18, 18, 16, 19,
		20, 21, 22, 22, 23, 20
	};

	const float x = size.x * 0.5f;
	const float y = size.y * 0.5f;
	const float z = size.z * 0.5f;
	Vector3 positions[] =
	{
		// Front
		{ -x, -y,  z },
		{  x, -y,  z },
		{  x,  y,  z },
		{ -x,  y,  z },

		// Back
		{ -x, -y, -z },
		{  x, -y, -z },
		{  x,  y, -z },
		{ -x,  y, -z },

		// Left
		{ -x, -y, -z },
		{ -x, -y,  z },
		{ -x,  y,  z },
		{ -x,  y, -z },

		// Right
		{  x, -y, -z },
		{  x, -y,  z },
		{  x,  y,  z },
		{  x,  y, -z },

		// Top
		{  -x,  y, -z },
		{   x,  y, -z },
		{   x,  y,  z },
		{  -x,  y,  z },

		// Bottom
		{  -x, -y, -z },
		{   x, -y, -z },
		{   x, -y,  z },
		{  -x, -y,  z }
	};

	return createGeometry(
		positions,
		normals,
		textureCoordinates,
		24,
		indices,
		36,
		options);
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

Geometry* GeometryFactoryC::createGeometry(
	const Vector3* positions,
	const Vector3* normals,
	const Vector2* textureCoordinates,
	u32 vertexCount,
	const u32* indices,
	u32 indexCount,
	const CreationOptions& options) noexcept
{
	try
	{
		std::vector<std::pair<Vector3, Vector3>> tb;
		if (options.tangentBitangent)
		{
			tb = getTangentBitangent(
				positions,
				vertexCount,
				textureCoordinates,
				indices,
				indexCount);
		}

		std::vector<float> vertexData;
		for (size_t i = 0; i < 24; ++i)
		{
			vertexData.push_back(positions[i].x);
			vertexData.push_back(positions[i].y);
			vertexData.push_back(positions[i].z);

			if (options.normal)
			{
				vertexData.push_back(normals[i].x);
				vertexData.push_back(normals[i].y);
				vertexData.push_back(normals[i].z);
			}

			if (options.textureCoordinates)
			{
				vertexData.push_back(textureCoordinates[i].x);
				vertexData.push_back(textureCoordinates[i].y);
			}

			if (options.tangentBitangent)
			{
				vertexData.push_back(tb[i].first.x);
				vertexData.push_back(tb[i].first.y);
				vertexData.push_back(tb[i].first.z);
				vertexData.push_back(tb[i].second.x);
				vertexData.push_back(tb[i].second.y);
				vertexData.push_back(tb[i].second.z);
			}
		}

		VertexFormat vertexFormat = VERTEX_FORMAT_POS3;
		u32 componentIndex = 1;
		if (options.normal)
		{
			vertexFormat.setComponentSize(componentIndex++, 3);
		}

		if (options.textureCoordinates)
		{
			vertexFormat.setComponentSize(componentIndex++, 2);
		}

		if (options.tangentBitangent)
		{
			vertexFormat.setComponentSize(componentIndex++, 3);
			vertexFormat.setComponentSize(componentIndex++, 3);
		}

		return mRenderer.getGeometries()->create(
			vertexFormat,
			vertexCount,
			vertexData.data(),
			indexCount,
			indices);
	}
	GLTUT_CATCH_ALL("Failed to create geometry");
	return nullptr;
}

// End of the namespace gltut
}
