#pragma once

// Includes
#include "engine/renderer/shader/Shader.h"

namespace gltut
{

class ShaderOpenGL final : public Shader
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	ShaderOpenGL(
		Renderer& renderer,
		const std::string& vertexCode,
		const std::string& fragmentCode);

	/// Destructor
	~ShaderOpenGL() noexcept final;

	/// Returns the location of a shader variable
	int32 getParameterLocation(const char* name) const noexcept final;

	/// Sets an integer value to a shader variable
	void setInt(int32 location, int value) noexcept final;

	/// Sets a float value to a shader variable
	void setFloat(int32 location, float value) noexcept final;

	/// Sets a 2D vector to a shader variable
	void setVec2(int32 location, float x, float y) noexcept final;

	/// Sets a 3D vector to a shader variable
	void setVec3(int32 location, float x, float y, float z) noexcept final;

	/// Sets a 4D vector to a shader variable
	void setVec4(int32 location, float x, float y, float z, float w) noexcept final;

	/// Sets a 3x3 matrix to a shader variable
	void setMat3(int32 location, const float* data) noexcept final;

	/// Sets a 4x4 matrix to a shader variable
	void setMat4(int32 location, const float* data) noexcept final;

	/// Returns the renderer associated with this shader
	Renderer* getRenderer() const noexcept final
	{
		return &mRenderer;
	}

	/// Binds the shader
	void bind() const noexcept final;
private:
	/// Renderer
	Renderer& mRenderer;

	/// Shader program
	unsigned mProgram;
};

// End of the namespace gltut
}
