#pragma once

// Includes
#include <vector>
#include "engine/core/NonCopyable.h"
#include "engine/math/Matrix4.h"
#include "engine/scene/nodes/SceneNode.h"

namespace gltut
{
// Global classes
/**
	\brief Template class for a scene node
	\tparam SceneNodeInterface The base class interface,
	assumed to be derived from SceneNode
*/
template <typename SceneNodeInterface>
class SceneNodeT : public SceneNodeInterface, public NonCopyable
{
public:
	/// Constructor
	SceneNodeT(
		const Matrix4& transform,
		SceneNode* parent) noexcept :
		mTransform(transform),
		mGlobalTransform(mTransform)
	{
		if (parent != nullptr)
		{
			parent->addChild(this);
		}
	}

	/// Returns the transform
	const Matrix4& getTransform() const noexcept final
	{
		return mTransform;
	}

	/// Sets the transform
	void setTransform(const Matrix4& transform) noexcept final
	{
		mTransform = transform;
		updateGlobalTransform();
	}

	/// Returns the global transform
	const Matrix4& getGlobalTransform() const noexcept final
	{
		return mGlobalTransform;
	}

	/// Returns the parent node
	const SceneNode* getParent() const noexcept final
	{
		return mParent;
	}

	/**
		\brief Adds a child node.
		Does nothing when: 
			- \p child is nullptr
			- \p child has a parent
			- \p child is already an anchestor of this node
	*/
	void addChild(SceneNode* child) noexcept final
	{
		if (child == nullptr || child->getParent() != nullptr)
		{
			return;
		}

		const SceneNode* node = this;
		while (node != nullptr)
		{
			// Prevent adding an anchestor node as a child
			if (node == child)
			{
				return;
			}
			node = node->getParent();
		}

		GLTUT_CATCH_ALL_BEGIN
			auto findResult = std::find(mChildren.begin(), mChildren.end(), child);
			if (findResult != mChildren.end())
			{
				return;
			}
			mChildren.push_back(child);
		GLTUT_CATCH_ALL_END("Failed to add child node")

		child->setParent(this);
	}

	/**
		\brief Removes a child node
		Does nothing when:
			- \p child is nullptr
			- \p child is not a child of this node
	*/
	void removeChild(SceneNode* child) noexcept final
	{
		if (child == nullptr || child->getParent() != this)
		{
			return;
		}

		GLTUT_CATCH_ALL_BEGIN
			const auto findResult = std::find(mChildren.begin(), mChildren.end(), child);
			GLTUT_CHECK(
				findResult != mChildren.end(),
				"The specified node is not a child of this node");
			mChildren.erase(findResult);
			child->setParent(nullptr);
		GLTUT_CATCH_ALL_END("Failed to remove child node")
	}

	/// Returns the number of children
	u32 getChildCount() const noexcept final
	{
		return static_cast<u32>(mChildren.size());
	}

	/// Returns a child node by index
	SceneNode* getChild(u32 index) noexcept final
	{
		return index < mChildren.size() ? mChildren[index] : nullptr;
	}

protected:
	/// Updates the global transform
	virtual void updateGlobalTransform() noexcept
	{
		mGlobalTransform = mParent != nullptr ? 
			mParent->getGlobalTransform() * mTransform :
			mTransform;

		for (SceneNode* child : mChildren)
		{
			child->updateGlobalTransform();
		}
	}

private:
	/// Sets the parent node. For internal use only.
	void setParent(SceneNode* parent) noexcept final
	{
		mParent = parent;
		updateGlobalTransform();
	}

	/// The parent node
	SceneNode* mParent = nullptr;

	/// The transform relative to the parent
	Matrix4 mTransform;

	/// The global transform
	Matrix4 mGlobalTransform;

	/// The child nodes
	std::vector<SceneNode*> mChildren;
};

// End of the namespace gltut
}
