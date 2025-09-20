#pragma once

// Includes
#include "SceneNodeT.h"

namespace gltut
{

// Global classes
/// Implementation of the group node abstraction
class GroupNodeC final : public SceneNodeT<SceneNode>
{
public:
	/// Constructor
	using SceneNodeT<SceneNode>::SceneNodeT;
};

// End of the namespace gltut
}
