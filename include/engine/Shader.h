#ifndef OPENGL_TUTORIALS_SHADER_H
#define OPENGL_TUTORIALS_SHADER_H

// Includes

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

	/// Sets a boolean value to a shader variable
	virtual void setBool(const char* name, bool value) noexcept = 0;

	/// Sets an integer value to a shader variable
	virtual void setInt(const char* name, int value) noexcept = 0;

	/// Sets a float value to a shader variable
	virtual void setFloat(const char* name, float value) noexcept = 0;
};

// End of the namespace gltut
}

#endif
