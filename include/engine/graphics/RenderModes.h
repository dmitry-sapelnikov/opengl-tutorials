#pragma once

namespace gltut
{
// Global enums
/// Face cull mode
enum class FaceCullingMode
{
	/// Render only front faces
	BACK = 0,
	/// Render only back faces
	FRONT,
	/// Render both front and back faces
	NONE
};

/// Depth function types
enum class DepthTestMode
{
	NEVER,
	LESS,
	EQUAL,
	LEQUAL,
	GREATER,
	NOTEQUAL,
	GEQUAL,
	ALWAYS
};

/// Polygon fill modes
enum class PolygonFillMode
{
	/// Fill polygons
	SOLID = 0,
	/// Draw polygon edges
	LINE,
	/// Draw polygon vertices
	POINT
};

// End of the namespace gltut
}
