#pragma once

// Includes
#include "SceneNodeT.h"

namespace gltut
{

/// A group scene node implementation
class GroupNodeC final : public SceneNodeT<SceneNode>
{
public:
	/// Constructor
	using SceneNodeT<SceneNode>::SceneNodeT;
};

// End of the namespace gltut
}
