#pragma once

// Includes
#include <array>
#include <string>
#include "engine/core/NonCopyable.h"
#include "engine/scene/shader/SceneShaderBinding.h"
#include "engine/scene/nodes/LightNode.h"

namespace gltut
{

/// Implementation of the SceneShaderBinding interface
class SceneShaderBindingC final : public SceneShaderBinding, public NonCopyable
{
public:
	/// Constructor
	explicit SceneShaderBindingC(Shader* shader) noexcept :
		mShader(shader)
	{
	}

	/// Returns the shader associated with this binding
	Shader* getShader() const noexcept final;

	/**
		\brief Sets the shader associated with this binding
		\param shader The shader to set
		\param resetParameters If true, clears all bound shader parameters
	*/
	void setShader(
		Shader* shader,
		bool resetParameters = false) noexcept final;

	/// Binds a scene object parameter to a shader parameter
	void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept final;

	/// Returns the name of a shader parameter bound to a scene object parameter
	const char* getBoundShaderParameter(
		Parameter parameter) const noexcept final;

	/// Updates the shader binding for a scene
	void update(const Scene* scene) const noexcept final;

	/// Updates the shader binding for a viewpoint
	void update(const Viewpoint* viewpoint) const noexcept final;

	/// Updates the shader binding for a geometry node
	void update(const GeometryNode* node) const noexcept final;

private:
	using ShaderParameterParts = std::pair<std::string, std::string>;

	/// Update the shader for a light
	void updateLight(
		const LightNode& light,
		u32 lightInd,
		SceneShaderBinding::Parameter position,
		SceneShaderBinding::Parameter ambientColor,
		SceneShaderBinding::Parameter diffuseColor,
		SceneShaderBinding::Parameter specularColor) const noexcept;

	/// Activates the shader binding for lights in a scene
	void updateLights(const Scene& scene) const;

	/// Return 2 parts of a shader parameter name
	const ShaderParameterParts& getShaderParameterParts(Parameter parameter) const noexcept;

	/// The shader associated with this binding
	Shader* mShader;

	/// Names of scene parameters
	std::array<std::string, static_cast<size_t>(Parameter::TOTAL_COUNT)> mShaderParameters;

	/// Names of scene parameters split into parts
	std::array<ShaderParameterParts, static_cast<size_t>(Parameter::TOTAL_COUNT)> mShaderParameterParts;
};

// End of the namespace gltut
}
