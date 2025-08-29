#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/renderer/objects/RenderObject.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderGroup: public RenderObject
{
public:
	class Sorter
	{
	public:
		virtual ~Sorter() noexcept = default;
		virtual bool operator()(
			const RenderObject* a,
			const RenderObject* b) const noexcept = 0;
	};

	/**
		Adds a render object to the group
		\note the method does not check cycles in groups
	*/
	virtual void add(RenderObject* object) noexcept = 0;

	/// Removes a render object from the group
	virtual void remove(RenderObject* object) noexcept = 0;

	/// Sorts the objects in the group using the specified sorter
	virtual void sort(const Sorter* sorter) noexcept = 0;
};

// End of the namespace gltut
}
