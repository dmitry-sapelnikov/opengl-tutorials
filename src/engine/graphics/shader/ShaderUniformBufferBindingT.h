#pragma once

// Includes
#include "engine/core/Check.h"
#include "engine/core/NonCopyable.h"
#include "engine/graphics/shader/ShaderUniformBuffer.h"
#include <array>
#include <string>

namespace gltut
{
// Global classes
/// Base implementation of the ShaderUniformBufferBinding interface
template <
	typename ShaderUniformBufferBindingInterface,
	typename ShaderUniformBufferBindingParameter>

class ShaderUniformBufferBindingT : public ShaderUniformBufferBindingInterface, public NonCopyable
{
public:
	/// Constructor
	explicit ShaderUniformBufferBindingT(ShaderUniformBuffer* target) noexcept
	{
		setTarget(target, true);
	}

	/// Returns the shader associated with this binding
	ShaderUniformBuffer* getTarget() const noexcept final
	{
		return mTarget;
	}

	/**
		\brief Sets the shader uniform buffer associated with this binding
		\param target The shader uniform buffer to associate with this binding
		\param resetParameters If true, clears all the bound parameters
	*/
	void setTarget(
		ShaderUniformBuffer* target,
		bool reset = false) noexcept final
	{
		mTarget = target;
		if (reset)
		{
			mParameterOffsets.fill(std::numeric_limits<u32>::max());
		}
	}

	/// Binds a parameter to a shader uniform buffer
	virtual void bind(
		typename ShaderUniformBufferBindingParameter parameter,
		u32 offset) noexcept final
	{
		const size_t index = static_cast<size_t>(parameter);
		if (GLTUT_ASSERT(index < static_cast<u32>(ShaderUniformBufferBindingParameter::TOTAL_COUNT)))
		{
			mParameterOffsets[index] = offset;
		}
	}

	/// Returns the name of a shader parameter bound to a scene parameter
	const u32* getParameterOffset(
		typename ShaderUniformBufferBindingParameter parameter) const noexcept final
	{
		const u32 result = mParameterOffsets[static_cast<size_t>(parameter)];
		return result == std::numeric_limits<u32>::max() ? nullptr : &result;
	}

private:
	/// The shader uniform buffer associated with this binding
	ShaderUniformBuffer* mTarget;

	/// Offsets of the parameters in the uniform buffer
	std::array<u32, static_cast<u32>(ShaderUniformBufferBindingParameter::TOTAL_COUNT)> mParameterOffsets;
};

// End of the namespace gltut
}
