#pragma once

// Includes
#include <vector>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/objects/RenderGeometryGroup.h"

namespace gltut
{
//	Global classes

///	Represents a render group
class RenderGeometryGroupC final : public RenderGeometryGroup, public NonCopyable
{
public:
	/// Adds a render geometry to the group
	void add(RenderGeometry* geometry) noexcept final
	{
		if (geometry != nullptr)
		{
			mGeometries.push_back(geometry);
		}
	}

	/// Removes a render geometry from the group
	void remove(RenderGeometry* geometry) noexcept final
	{
		auto it = std::find(
			mGeometries.begin(),
			mGeometries.end(),
			geometry);
		if (it != mGeometries.end())
		{
			mGeometries.erase(it);
		}
	}

	/// Returns the number of geometries in the group
	u32 getSize() const noexcept final
	{
		return static_cast<u32>(mGeometries.size());
	}

	/// Return the i-th geometry in the group
	RenderGeometry* get(u32 index) const noexcept final
	{
		return index < mGeometries.size() ? mGeometries[index] : nullptr;
	}

	/// Removes all geometries from the group
	void clear() noexcept final
	{
		mGeometries.clear();
	}

	/// Renders all objects in the group
	void render(u32 materialPass) const noexcept final
	{
		for (const auto& geometry : mGeometries)
		{
			geometry->render(materialPass);
		}
	}

	/// Returns the start iterator
	auto begin() noexcept
	{
		return mGeometries.begin();
	}

	/// Returns the end iterator
	auto end() noexcept
	{
		return mGeometries.end();
	}

private:
	std::vector<RenderGeometry*> mGeometries;
};

// End of the namespace gltut
}
