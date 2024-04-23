#ifndef OPENGL_TUTORIALS_SHADER_H
#define OPENGL_TUTORIALS_SHADER_H

// Includes
#include "engine/core/Types.h"

namespace gltut
{
//	Global classes
///	Represents a shader
class Shader
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Activates the shader
	virtual void use() noexcept = 0;

	/// Returns the location of a shader variable
	virtual int32 getVariableLocation(const char* name) noexcept = 0;

	/// Sets a boolean value to a shader variable
	virtual void setBool(const char* name, bool value) noexcept = 0;

	/// Sets an integer value to a shader variable
	virtual void setInt(const char* name, int value) noexcept = 0;

	/// Sets a float value to a shader variable
	virtual void setFloat(const char* name, float value) noexcept = 0;

	/// Sets a 2D vector to a shader variable
	virtual void setVec2(const char* name, float x, float y) noexcept = 0;

	/// Sets a 3D vector to a shader variable
	virtual void setVec3(const char* name, float x, float y, float z) noexcept = 0;

	/// Sets a 4D vector to a shader variable
	virtual void setVec4(const char* name, float x, float y, float z, float w) noexcept = 0;

	/// Sets a 4x4 matrix to a shader variable
	virtual void setMat4(const char* name, const float* data) noexcept = 0;

	/// Returns the name of the model matrix variable
	virtual const char* getModelMatrixName() const noexcept = 0;

	/// Sets the name of the model matrix variable
	virtual void setModelMatrixName(const char* name) noexcept = 0;

	/// Returns the name of the view matrix variable
	virtual const char* getViewMatrixName() const noexcept = 0;

	/// Sets the name of the view matrix variable
	virtual void setViewMatrixName(const char* name) noexcept = 0;

	/// Returns the name of the projection matrix variable
	virtual const char* getProjectionMatrixName() const noexcept = 0;

	/// Sets the name of the projection matrix variable
	virtual void setProjectionMatrixName(const char* name) noexcept = 0;
};

// End of the namespace gltut
}

#endif
