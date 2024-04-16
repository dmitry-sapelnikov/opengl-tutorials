#ifndef OPENGL_TUTORIALS_SHADER_OPEN_GL_H
#define OPENGL_TUTORIALS_SHADER_OPEN_GL_H

// Includes
#include <string>
#include "engine/Shader.h"
#include "engine/core/NonCopyable.h"

namespace gltut
{

class ShaderOpenGL final : public Shader, public NonCopyable
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
	void use() noexcept final;

	/// Sets a boolean value to a shader variable
	void setBool(const char* name, bool value) noexcept final;

	/// Sets an integer value to a shader variable
	void setInt(const char* name, int value) noexcept final;

	/// Sets a float value to a shader variable
	void setFloat(const char* name, float value) noexcept final;

private:
	/// Shader program
	unsigned mProgram = 0;
};

// End of the namespace gltut
}

#endif
