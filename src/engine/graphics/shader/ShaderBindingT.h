#pragma once

// Includes
#include <array>
#include <string>
#include "engine/core/NonCopyable.h"
#include "engine/graphics/shader/Shader.h"

namespace gltut
{
// Global classes
/// Base implementation of the ShaderBinding interface
template <typename ShaderBindingInterface>
class ShaderBindingT : public ShaderBindingInterface, public NonCopyable
{
public:
	/// Shader parameter parts
	using ShaderParameterParts = std::pair<std::string, std::string>;


	/// Constructor
	explicit ShaderBindingT(Shader* shader) noexcept :
		mShader(shader)
	{
	}

	/// Returns the shader associated with this binding
	Shader* getShader() const noexcept final
	{
		return mShader;
	}

	/**
		\brief Sets the shader associated with this binding
		\param shader The shader to set
		\param resetParameters If true, clears all bound shader parameters
	*/
	void setShader(
		Shader* shader,
		bool resetParameters = false) noexcept final
	{
		mShader = shader;
		if (resetParameters)
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
		typename ShaderBindingInterface::Parameter parameter,
		const char* shaderParameter) noexcept final
	{
		const size_t index = static_cast<size_t>(parameter);
		if (index >= static_cast<u32>(ShaderBindingInterface::Parameter::TOTAL_COUNT))
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
			mShaderParameterParts[index] = { param.substr(0, dotPos), param.substr(dotPos + 1) };
		}
		else
		{
			// No dot found, use the whole name as the first part
			mShaderParameterParts[index] = { param, "" };
		}

		if (!mShaderParameterParts[index].second.empty())
		{
			GLTUT_ASSERT(!mShaderParameterParts[index].first.empty());
		}
	}

	/// Returns the name of a shader parameter bound to a scene parameter
	const char* getBoundShaderParameter(
		typename ShaderBindingInterface::Parameter parameter) const noexcept final
	{
		const auto& result = mShaderParameters[static_cast<size_t>(parameter)];
		return result.empty() ? nullptr : result.c_str();
	}

protected:
	/// Return 2 parts of a shader parameter name
	const ShaderParameterParts& getShaderParameterParts(
		typename ShaderBindingInterface::Parameter parameter) const noexcept
	{
		return mShaderParameterParts[static_cast<size_t>(parameter)];
	}

private:
	/// The shader associated with this binding
	Shader* mShader;

	/// Names of scene parameters
	std::array<std::string, static_cast<u32>(ShaderBindingInterface::Parameter::TOTAL_COUNT)> mShaderParameters;

	/// Names of scene parameters split into parts
	std::array<ShaderParameterParts, static_cast<u32>(ShaderBindingInterface::Parameter::TOTAL_COUNT)> mShaderParameterParts;
};

// End of the namespace gltut
}
