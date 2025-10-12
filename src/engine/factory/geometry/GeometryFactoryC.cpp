// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "GeometryFactoryC.h"
#include "engine/math/Vector3.h"
#include <array>
#include <vector>

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
Geometry* GeometryFactoryC::createQuad(
	const Vector2& size,
	const CreationOptions& options) noexcept
{
	static constexpr Vector3 normals[] =
		{
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f}};

	static constexpr Vector2 textureCoordinates[] =
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}};

	static constexpr u32 indices[] = {0, 1, 2, 2, 3, 0};

	const float x = size.x * 0.5f;
	const float y = size.y * 0.5f;
	const Vector3 positions[] =
		{
			{-x, -y, 0.0f},
			{x, -y, 0.0f},
			{x, y, 0.0f},
			{-x, y, 0.0f}};

	return createGeometry(
		positions,
		normals,
		textureCoordinates,
		4,
		indices,
		6,
		options);
}

Geometry* GeometryFactoryC::createPlane(
	const Vector2& size,
	const Point2u& subdivisions,
	const CreationOptions& options) noexcept
{
	if (!GLTUT_ASSERT(subdivisions.x > 0 && subdivisions.y > 0))
	{
		return nullptr;
	}

	Geometry* result = nullptr;
	std::vector<Vector3> positions;
	positions.reserve((subdivisions.x + 1) * (subdivisions.y + 1));

	std::vector<Vector2> textureCoordinates;
	if (options.textureCoordinates)
	{
		textureCoordinates.reserve((subdivisions.x + 1) * (subdivisions.y + 1));
	}

	std::vector<u32> indices;
	indices.reserve(subdivisions.x * subdivisions.y * 6);

	const float xStep = size.x / subdivisions.x;
	const float yStep = size.y / subdivisions.y;

	const float xStart = -0.5f * size.x;
	const float yStart = -0.5f * size.y;

	for (u32 yInd = 0; yInd <= subdivisions.y; ++yInd)
	{
		const float y = yStart + static_cast<float>(yInd) * yStep;
		const float t = static_cast<float>(yInd) / subdivisions.y;
		for (u32 xInd = 0; xInd <= subdivisions.x; ++xInd)
		{
			const float x = xStart + static_cast<float>(xInd) * xStep;
			const float s = static_cast<float>(xInd) / subdivisions.x;
			positions.push_back({ x, y, 0.0f });
			if (options.textureCoordinates)
			{
				textureCoordinates.push_back({ s, t });
			}

			if (xInd != subdivisions.x && yInd != subdivisions.y)
			{
				const u32 i0 = yInd * (subdivisions.x + 1) + xInd;
				const u32 i1 = i0 + 1;
				const u32 i2 = i0 + (subdivisions.x + 1);
				const u32 i3 = i2 + 1;
				indices.push_back(i0);
				indices.push_back(i1);
				indices.push_back(i3);
				indices.push_back(i3);
				indices.push_back(i2);
				indices.push_back(i0);
			}
		}
	}

	std::vector<Vector3> normals;
	if (options.normal)
	{
		normals.resize(positions.size(), { 0.0f, 0.0f, 1.0f });
	}

	return createGeometry(
		positions.data(),
		normals.data(),
		textureCoordinates.data(),
		static_cast<u32>(positions.size()),
		indices.data(),
		static_cast<u32>(indices.size()),
		options);
}

Geometry* GeometryFactoryC::createBox(
	const Vector3& size,
	const CreationOptions& options) noexcept
{
	static constexpr Vector3 normals[] =
		{
			// Front
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},

			// Back
			{0.0f, 0.0f, -1.0f},
			{0.0f, 0.0f, -1.0f},
			{0.0f, 0.0f, -1.0f},
			{0.0f, 0.0f, -1.0f},

			// Left
			{-1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f},

			// Right
			{1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},

			// Top
			{0.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},

			// Bottom
			{0.0f, -1.0f, 0.0f},
			{0.0f, -1.0f, 0.0f},
			{0.0f, -1.0f, 0.0f},
			{0.0f, -1.0f, 0.0f}};

	static constexpr Vector2 textureCoordinates[] =
		{
			// Front
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			// Back
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			// Left
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			// Right
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			// Top
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			// Bottom
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}};

	static constexpr u32 indices[] =
		{
			0, 1, 2, 2, 3, 0,
			5, 4, 6, 6, 4, 7,
			8, 9, 10, 10, 11, 8,
			13, 12, 14, 14, 12, 15,
			17, 16, 18, 18, 16, 19,
			20, 21, 22, 22, 23, 20};

	const float x = size.x * 0.5f;
	const float y = size.y * 0.5f;
	const float z = size.z * 0.5f;
	Vector3 positions[] =
		{
			// Front
			{-x, -y, z},
			{x, -y, z},
			{x, y, z},
			{-x, y, z},

			// Back
			{-x, -y, -z},
			{x, -y, -z},
			{x, y, -z},
			{-x, y, -z},

			// Left
			{-x, -y, -z},
			{-x, -y, z},
			{-x, y, z},
			{-x, y, -z},

			// Right
			{x, -y, -z},
			{x, -y, z},
			{x, y, z},
			{x, y, -z},

			// Top
			{-x, y, -z},
			{x, y, -z},
			{x, y, z},
			{-x, y, z},

			// Bottom
			{-x, -y, -z},
			{x, -y, -z},
			{x, -y, z},
			{-x, -y, z}};

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
			const Vector3 normal = setDistanceAzimuthInclination({1.0, longitude, latitude});

			// setDistanceAzimuthInclination uses z-axis as the up vector, so
			// so we need to swap the x and z components to use y-axis as the up vector
			vertices.push_back({radius * normal.x,
								radius * normal.z,
								radius * normal.y,
								normal.x,
								normal.z,
								normal.y,
								static_cast<float>(lonInd) / lonSubdivisions,
								static_cast<float>(latInd) / latSubdivisions});
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

Geometry* GeometryFactoryC::createCylinder(
	float radius,
	float height,
	u32 radialSubdivisions,
	bool addCaps,
	const CreationOptions& options) noexcept
{
	Geometry* result = nullptr;
	try
	{
		GLTUT_CHECK(radialSubdivisions >= 3, "radialSubdivisions must be >= 3");
		std::vector<Vector3> positions;
		positions.reserve(2 * (radialSubdivisions + 1));
		std::vector<Vector3> normals;
		if (options.normal)
		{
			normals.reserve(2 * (radialSubdivisions + 1));
		}

		std::vector<Vector2> textureCoordinates;
		if (options.textureCoordinates)
		{
			textureCoordinates.reserve(2 * (radialSubdivisions + 1));
		}

		std::vector<u32> indices;
		indices.reserve(6 * radialSubdivisions);

		const float angleStep = 2.0f * PI / radialSubdivisions;
		const float halfHeight = height * 0.5f;

		for (u32 h = 0; h < 2; ++h)
		{
			const float y = (h == 0) ? -halfHeight : halfHeight;
			const float t = (h == 0) ? 0.0f : 1.0f;
			for (u32 i = 0; i <= radialSubdivisions; ++i)
			{
				const float angle = static_cast<float>(i) * angleStep;
				const float x = radius * std::cos(angle);
				const float z = radius * std::sin(angle);
				positions.push_back({x, y, z});
				if (options.normal)
				{
					const Vector3 normal = {x, 0.0f, z};
					normals.push_back(normal.getNormalized());
				}
				if (options.textureCoordinates)
				{
					const float s = static_cast<float>(i) / radialSubdivisions;
					textureCoordinates.push_back({s, t});
				}
			}
		}

		addFacesBetweenCircles(
			0,
			radialSubdivisions + 1,
			radialSubdivisions + 1,
			indices);

		if (addCaps)
		{
			// Copy the top and bottom vertices, change their normals and texture coordinates
			positions.insert(
				positions.end(),
				positions.begin(),
				positions.end());

			if (options.normal)
			{
				for (u32 h = 0; h < 2; ++h)
				{
					const Vector3 normal = (h == 0) ? Vector3{0.0f, -1.0f, 0.0f} : Vector3{0.0f, 1.0f, 0.0f};
					for (u32 i = 0; i <= radialSubdivisions; ++i)
					{
						normals.push_back(normal);
					}
				}
			}

			if (options.textureCoordinates)
			{
				// Set 0, 0 for bottom face and 0, 1 for top face
				for (u32 h = 0; h < 2; ++h)
				{
					const float t = (h == 0) ? 0.0f : 1.0f;
					for (u32 i = 0; i <= radialSubdivisions; ++i)
					{
						textureCoordinates.push_back({float(i) / radialSubdivisions, t});
					}
				}
			}

			// Create tri-fan for the bottom face
			for (u32 h = 0; h < 2; ++h)
			{
				u32 bottomFaceOffset = (2 + h) * (radialSubdivisions + 1);
				for (u32 i = 1; i < radialSubdivisions; ++i)
				{
					indices.push_back(bottomFaceOffset); // center vertex
					indices.push_back(bottomFaceOffset + i + (h != 0));
					indices.push_back(bottomFaceOffset + i + (h == 0));
				}
			}
		}

		result = createGeometry(
			positions.data(),
			normals.data(),
			textureCoordinates.data(),
			static_cast<u32>(positions.size()),
			indices.data(),
			static_cast<u32>(indices.size()),
			options);
	}
	GLTUT_CATCH_ALL("Failed to create a cylinder geometry")
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
		for (size_t i = 0; i < vertexCount; ++i)
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
