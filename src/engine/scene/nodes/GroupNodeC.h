// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

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
