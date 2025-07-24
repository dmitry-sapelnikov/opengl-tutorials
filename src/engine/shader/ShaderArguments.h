#ifndef OPENGL_TUTORIALS_SHADER_ARGUMENTS_H
#define OPENGL_TUTORIALS_SHADER_ARGUMENTS_H

// Includes
#include <array>
#include <string>
#include <variant>
#include <vector>

#include "engine/core/NonCopyable.h"

#include "engine/math/Vector3.h"
#include "engine/math/Matrix3.h"
#include "engine/math/Matrix4.h"

#include "engine/shader/Shader.h"

namespace gltut
{

/// Represents a set of shader parameter values (like function arguments)
class ShaderArguments final : public ShaderParameters, public NonCopyable
{
public:
	/// Parameter value
	using ParameterValue = std::variant<
		int,
		float,
		std::array<float, 2>,
		std::array<float, 3>,
		std::array<float, 4>,
		Matrix3,
		Matrix4>;

	/// Vector of shader parameter locations and their values
	using ParameterValues = std::vector<std::pair<int32, ParameterValue>>;

	/// Constructor
	explicit ShaderArguments(Shader* shader) noexcept;

	/// Returns the associated shader
	Shader* getShader() const noexcept;

	/// Sets the shader. If the shader changes, resets all the parameter values
	void setShader(Shader* shader) noexcept;

	/// Returns the parameter location
	int32 getParameterLocation(const char* name) const noexcept final;

	/// Sets an integer value to a shader parameter
	void setInt(int32 location, int value) noexcept final;

	/// Sets a float value to a shader parameter
	void setFloat(int32 location, float value) noexcept final;

	/// Sets a 2D vector to a shader parameter
	void setVec2(int32 location, float x, float y) noexcept final;

	/// Sets a 3D vector to a shader parameter
	void setVec3(int32 location, float x, float y, float z) noexcept final;

	/// Sets a 4D vector to a shader parameter
	void setVec4(int32 location, float x, float y, float z, float w) noexcept final;

	/// Sets a 3x3 matrix to a shader parameter
	void setMat3(int32 location, const float* data) noexcept final;

	/// Sets a 4x4 matrix to a shader parameter
	void setMat4(int32 location, const float* data) noexcept final;

	/**
		\brief Sets the controlled shader as the current one,
		then sets the shader parameters
	*/
	void activate() const noexcept;

private:
	/// Associated shader
	Shader* mShader;

	/// Shader parameter values
	ParameterValues mParameterValues;
};

// End of the namespace gltut
}

#endif
