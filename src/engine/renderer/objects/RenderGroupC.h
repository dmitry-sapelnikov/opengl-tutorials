#pragma once

// Includes
#include <vector>
#include "engine/renderer/objects/RenderGroup.h"

namespace gltut
{
//	Global classes

///	Represents a render pass of the scene
class RenderGroupC final : public RenderGroup, public NonCopyable
{
public:
	/// Adds a render object to the group
	void addObject(RenderObject* object) noexcept final
	{
		if (object != nullptr)
		{
			mObjects.push_back(object);
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

private:
	std::vector<RenderObject*> mObjects;
};

// End of the namespace gltut
}
