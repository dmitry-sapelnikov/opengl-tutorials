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
	enum class Matrix
	{
		MODEL = 0,
		VIEW,
		PROJECTION,
		NORMAL,
		/// Total number of standard matrices
		TOTAL_COUNT
	};

	/// Returns the name of standard matrix variable
	virtual const char* getMatrixName(Matrix matrix) const noexcept = 0;

	/// Sets the name of the standard matrix variable
	virtual void setMatrixName(Matrix matrix, const char* name) noexcept = 0;

	/// Activates the shader
	virtual void activate() const noexcept = 0;
};

// End of the namespace gltut
}

#endif
