#ifndef OPENGL_TUTORIALS_IMESH_H
#define OPENGL_TUTORIALS_IMESH_H

// Includes
#include "engine/core/Types.h"

namespace gltut
{

/// The class represents a triangle mesh
class IMesh
{
public:
	/// Virtual destructor
	virtual ~IMesh() noexcept = default;

	/// Renders the mesh
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
