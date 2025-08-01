#pragma once

// Includes
#include "engine/math/Matrix4.h"

namespace gltut
{

// Global classes
/// Contains the colors used for a light source
class SceneNode
{
public:
	/// Virtual destructor
	virtual ~SceneNode() noexcept = default;

	/// Returns the transform relative to the parent
	virtual const Matrix4& getTransform() const noexcept = 0;

	/// Sets the transform relative to the parent
	virtual void setTransform(const Matrix4& transform) noexcept = 0;

	/// Returns the global transform
	virtual const Matrix4& getGlobalTransform() const noexcept = 0;

	/// Returns the parent of this node
	virtual const SceneNode* getParent() const noexcept = 0;

	/**
		\brief Adds a child node.
		Does nothing when:
			- \p child is nullptr
			- \p child has a parent
			- \p child is already an anchestor of this node
	*/
	virtual void addChild(SceneNode* child) noexcept = 0;

	/**
		\brief Removes a child node
		Does nothing when:
			- \p child is nullptr
			- \p child is not a child of this node
	*/
	virtual void removeChild(SceneNode* child) noexcept = 0;

	/// Returns the number of children
	virtual u32 getChildCount() const noexcept = 0;

	/// Returns a child node by index
	virtual SceneNode* getChild(u32 index) noexcept = 0;

private:
	/// Friend implementation class
	template <typename SceneNodeInterface>
	friend class SceneNodeT;

	/// Updates the global transform
	virtual void updateGlobalTransform() noexcept = 0;

	/// Sets the parent of this node
	virtual void setParent(SceneNode* parent) noexcept = 0;
};

// End of the namespace gltut
}
