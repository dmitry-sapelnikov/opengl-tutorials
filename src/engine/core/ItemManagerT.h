// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once
#include "engine/core/Check.h"
#include "engine/core/NonCopyable.h"
#include "engine/core/Types.h"
#include <memory>
#include <vector>

namespace gltut
{

template <typename ItemManagerInterface>
class ItemManagerT : public ItemManagerInterface, public NonCopyable
{
public:
	using ItemType = typename ItemManagerInterface::ItemType;

	/// Removes the item from the manager
	void remove(ItemType* item) noexcept final
	{
		if (item == nullptr)
		{
			return;
		}
		auto it = std::find_if(
			mItems.begin(),
			mItems.end(),
			[item](const std::unique_ptr<ItemType>& itemPtr)
			{
				return itemPtr.get() == item;
			});
		if (it != mItems.end())
		{
			mItems.erase(it);
		}
	}

	/// Returns the number of items managed
	u32 size() const noexcept final
	{
		return static_cast<u32>(mItems.size());
	}

	/// Returns the item at the given index
	ItemType* get(u32 index) const noexcept final
	{
		if (index >= mItems.size())
		{
			return nullptr;
		}
		return mItems[index].get();
	}

protected:
	ItemType* add(std::unique_ptr<ItemType> item)
	{
		GLTUT_CHECK(item != nullptr, "Cannot add a null item");
		return mItems.emplace_back(std::move(item)).get();
	}

	std::vector<std::unique_ptr<ItemType>> mItems;
};

} // namespace gltut