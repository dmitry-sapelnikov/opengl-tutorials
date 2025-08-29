#pragma once
#include "engine/core/Types.h"
#include "engine/math/Matrix4.h"

namespace gltut
{
//	Global classes
///	Represents a base class for render objects
class RenderObject
{
public:
	/// Virtual destructor
	virtual ~RenderObject() noexcept = default;

	/// Returns the transformation matrix
	virtual Matrix4 getTransform() const noexcept = 0;

	/// Renders the object
	virtual void render(u32 materialPass) const noexcept = 0;
};

// End of the namespace gltut
}
