#ifndef OPENGL_TUTORIALS_SHADER_H
#define OPENGL_TUTORIALS_SHADER_H

// Includes
#include "engine/core/Check.h"
#include "ShaderParameters.h"

namespace gltut
{
//	Global classes
///	Represents a shader
class Shader: public ShaderParameters
{
public:
	/// Enum of standard matrices
	enum class SceneParameter
	{
		// Model matrix
		MODEL = 0,
		/// View matrix
		VIEW,
		/// Projection matrix
		PROJECTION,
		/// Normal matrix
		NORMAL,
		/// View position
		VIEW_POSITION,
		/// Total number of standard matrices
		TOTAL_COUNT
	};

	/// Returns the name of a scene parameter
	virtual const char* getSceneParameterName(SceneParameter parameter) const noexcept = 0;

	/// Sets the name of a scene parameter
	virtual void setSceneParameterName(SceneParameter parameter, const char* name) noexcept = 0;

	/// Activates the shader
	virtual void activate() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
