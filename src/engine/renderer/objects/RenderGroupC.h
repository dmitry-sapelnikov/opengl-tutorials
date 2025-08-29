#pragma once

// Includes
#include <vector>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/objects/RenderGroup.h"

namespace gltut
{
//	Global classes

///	Represents a render group
class RenderGroupC final : public RenderGroup, public NonCopyable
{
public:
	/// Adds a render object to the group
	void add(RenderObject* object) noexcept final
	{
		if (object != nullptr)
		{
			mObjects.push_back(object);
		}
	}

	/// Removes a render object from the group
	void remove(RenderObject* object) noexcept final
	{
		auto it = std::find(
			mObjects.begin(),
			mObjects.end(),
			object);
		if (it != mObjects.end())
		{
			mObjects.erase(it);
		}
	}

	/// Renders all objects in the group
	void render(u32 materialPass) const noexcept final
	{
		for (const auto& object : mObjects)
		{
			object->render(materialPass);
		}
	}

	/// Sorts the objects in the group using the specified sorter
	void sort(const Sorter* sorter) noexcept final
	{
		if (sorter != nullptr)
		{
			std::sort(
				mObjects.begin(),
				mObjects.end(),
				[&sorter](const RenderObject* a, const RenderObject* b)
				{
					return (*sorter)(a, b);
				});
		}
	}

private:
	std::vector<RenderObject*> mObjects;
};

// End of the namespace gltut
}
