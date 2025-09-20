// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/shader/Shader.h"
#include <array>
#include <string>

namespace gltut
{
// Global classes
/// Base implementation of the ShaderBinding interface
template <typename ShaderBindingInterface, typename ShaderBindingParameter>
class ShaderBindingT : public ShaderBindingInterface, public NonCopyable
{
public:
	/// Shader parameter parts
	using ShaderParameterParts = std::pair<std::string, std::string>;

	/// Constructor
	explicit ShaderBindingT(Shader* shader) noexcept :
		mTarget(shader)
	{
	}

	/// Returns the shader associated with this binding
	Shader* getTarget() const noexcept final
	{
		return mTarget;
	}

	/**
		\brief Sets the shader associated with this binding
		\param shader The shader to set
		\param resetParameters If true, clears all bound shader parameters
	*/
	void setTarget(
		Shader* target,
		bool reset = false) noexcept final
	{
		mTarget = target;
		if (reset)
		{
			for (auto& name : mShaderParameters)
			{
				name.clear();
			}

			for (auto& parts : mShaderParameterParts)
			{
				parts.first.clear();
				parts.second.clear();
			}
		}
	}

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		typename ShaderBindingParameter parameter,
		const char* shaderParameter) noexcept final
	{
		const size_t index = static_cast<size_t>(parameter);
		if (index >= static_cast<u32>(ShaderBindingParameter::TOTAL_COUNT))
		{
			return;
		}

		const std::string param((shaderParameter != nullptr) ? shaderParameter : "");

		mShaderParameters[index] = param;

		// Find the first dot in the shader parameter name
		size_t dotPos = param.find('.');
		if (dotPos != std::string::npos)
		{
			// Split the shader parameter name into two parts
			mShaderParameterParts[index] = {param.substr(0, dotPos), param.substr(dotPos + 1)};
		}
		else
		{
			// No dot found, use the whole name as the first part
			mShaderParameterParts[index] = {param, ""};
		}

		if (!mShaderParameterParts[index].second.empty())
		{
			GLTUT_ASSERT(!mShaderParameterParts[index].first.empty());
		}
	}

	/// Returns the name of a shader parameter bound to a scene parameter
	const char* getBoundShaderParameter(
		typename ShaderBindingParameter parameter) const noexcept final
	{
		const auto& result = mShaderParameters[static_cast<size_t>(parameter)];
		return result.empty() ? nullptr : result.c_str();
	}

protected:
	/// Return 2 parts of a shader parameter name
	const ShaderParameterParts& getShaderParameterParts(
		typename ShaderBindingParameter parameter) const noexcept
	{
		return mShaderParameterParts[static_cast<size_t>(parameter)];
	}

private:
	/// The shader associated with this binding
	Shader* mTarget;

	/// Names of scene parameters
	std::array<std::string, static_cast<u32>(ShaderBindingParameter::TOTAL_COUNT)> mShaderParameters;

	/// Names of scene parameters split into parts
	std::array<ShaderParameterParts, static_cast<u32>(ShaderBindingParameter::TOTAL_COUNT)> mShaderParameterParts;
};

// End of the namespace gltut
}
