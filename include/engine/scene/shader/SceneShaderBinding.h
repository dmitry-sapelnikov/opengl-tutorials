#pragma once

// Includes
#include "engine/renderer/shader/Shader.h"

namespace gltut
{
//	Global classes
class Scene;
class GeometryNode;

/// The class represents a shader binding for scene parameters
class SceneShaderBinding
{
public:
	/// Enum of standard matrices
	enum class Parameter
	{
		/// Camera view matrix
		CAMERA_VIEW_MATRIX = 0,
		/// Camera projection matrix
		CAMERA_PROJECTION_MATRIX,
		/// Camera view position
		CAMERA_POSITION,

		/// Scene node matrix (model matrix)
		NODE_MATRIX,
		/// Scene node normal matrix
		NODE_NORMAL_MATRIX,

		/// Total number of scene parameters
		TOTAL_COUNT
	};

	/// Virtual destructor
	virtual ~SceneShaderBinding() noexcept = default;

	/// Returns the shader associated with this binding
	virtual Shader* getShader() const noexcept = 0;

	/**
		\brief Sets the shader associated with this binding
		\param shader The shader to set
		\param resetParameters If true, clears all bound shader parameters
	*/
	virtual void setShader(
		Shader* shader,
		bool resetParameters = false) noexcept = 0;

	/// Binds a scene object parameter to a shader parameter
	virtual void bind(
		Parameter parameter,
		const char* shaderParameter) noexcept = 0;

	/// Returns the name of a shader parameter bound to a scene parameter
	virtual const char* getBoundShaderParameter(
		Parameter parameter) const noexcept = 0;

	/// Activates the shader binding for a scene
	virtual void activate(const Scene* scene) const noexcept = 0;

	/// Activates the shader binding for a scene object
	virtual void activate(const GeometryNode* node) const noexcept = 0;
};

// Global functions
/**
	\brief Binds model, view, and projection matrices
	\param binding The shader binding to use
	\param modelMatrix The model matrix shader parameter
	\param viewMatrix The view matrix shader parameter
	\param projectionMatrix The projection matrix shader parameter
	
	\note Every string argument can be set to nullptr
	to skip binding of that parameter.
*/
inline void bindModelViewProjectionShaderParameters(
	SceneShaderBinding* binding,
	const char* modelMatrix,
	const char* viewMatrix,
	const char* projectionMatrix) noexcept
{
	if (binding == nullptr)
	{
		return;
	}
	binding->bind(SceneShaderBinding::Parameter::NODE_MATRIX, modelMatrix);
	binding->bind(SceneShaderBinding::Parameter::CAMERA_VIEW_MATRIX, viewMatrix);
	binding->bind(SceneShaderBinding::Parameter::CAMERA_PROJECTION_MATRIX, projectionMatrix);
}

// End of the namespace gltut
}
