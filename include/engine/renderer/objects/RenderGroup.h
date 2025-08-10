#pragma once

// Includes
#include "engine/renderer/objects/RenderObject.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderGroup: public RenderObject
{
public:
	/**
		Adds a render object to the group
		\note the method does not check cycles in groups
	*/
	virtual void addObject(RenderObject* object) noexcept = 0;
};

// End of the namespace gltut
}
