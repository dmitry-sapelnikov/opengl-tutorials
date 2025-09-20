// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/Types.h"

namespace gltut
{
// Global classes
/**
	Interface for item management.
	Creation / serialization methods are defined in the derived classes.
*/
template <typename ItemT>
class ItemManager
{
public:
	/// Type of the items managed
	using ItemType = ItemT;

	/// Virtual destructor
	virtual ~ItemManager() = default;

	/// Removes the item from the manager
	virtual void remove(ItemType* item) noexcept = 0;

	/// Returns the number of items managed
	virtual u32 size() const noexcept = 0;

	/// Returns the item at the given index
	virtual ItemType* get(u32 index) const noexcept = 0;
};

// namespace gltut
}