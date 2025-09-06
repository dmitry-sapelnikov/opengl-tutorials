#pragma once
// Includes

namespace gltut
{

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

// End of the namespace gltut
}
