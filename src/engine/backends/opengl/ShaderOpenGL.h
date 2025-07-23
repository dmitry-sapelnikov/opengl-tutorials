#ifndef OPENGL_TUTORIALS_SHADER_OPEN_GL_H
#define OPENGL_TUTORIALS_SHADER_OPEN_GL_H

// Includes
#include <string>
#include <unordered_map>
#include "../../ShaderC.h"

namespace gltut
{

class ShaderOpenGL final : public ShaderC
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	ShaderOpenGL(
		const std::string& vertexCode,
		const std::string& fragmentCode);

	/// Destructor
	~ShaderOpenGL() noexcept final;

	/// Activates the shader
	void activate() const noexcept final;

	/// Sets an bool value to a shader variable
	void setBool(const char* name, bool value) noexcept final;

	/// Sets an integer value to a shader variable
	void setInt(const char* name, int value) noexcept final;

	/// Sets a float value to a shader variable
	void setFloat(const char* name, float value) noexcept final;

	/// Sets a 2D vector to a shader variable
	void setVec2(const char* name, float x, float y) noexcept final;

	/// Sets a 3D vector to a shader variable
	void setVec3(const char* name, float x, float y, float z) noexcept final;

	/// Sets a 4D vector to a shader variable
	void setVec4(const char* name, float x, float y, float z, float w) noexcept final;

	/// Sets a 3x3 matrix to a shader variable
	void setMat3(const char* name, const float* data) noexcept final;

	/// Sets a 4x4 matrix to a shader variable
	void setMat4(const char* name, const float* data) noexcept final;

private:
	/// Returns the location of a shader variable
	int32 getVariableLocation(const char* name) noexcept;

	/// Gets the location of a shader variable with error checking
	int getCheckedVariableLocation(const char* name) noexcept;

	/// Shader program
	unsigned mProgram = 0;

	/// Cached variable locations
	std::unordered_map<std::string, int> mVariableLocations;
};

// End of the namespace gltut
}

#endif
