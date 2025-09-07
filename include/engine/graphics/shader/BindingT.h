#pragma once

// Includes

namespace gltut
{
//	Global classes
/// The class represents a binding of a target object
template <typename TargetType>
class BindingT
{
public:
	/// Virtual destructor
	virtual ~BindingT() noexcept = default;

	/// Returns the target associated with this binding
	virtual TargetType* getTarget() const noexcept = 0;

	/**
		\brief Sets the target to bind
		\param target The target to bind
		\param reset If true, clears all bound target parameters
	*/
	virtual void setTarget(
		TargetType* shader,
		bool reset = false) noexcept = 0;
};

// End of the namespace gltut
}
