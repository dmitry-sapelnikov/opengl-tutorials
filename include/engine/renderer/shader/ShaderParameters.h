#pragma once

// Includes
#include "engine/core/Check.h"
#include "engine/core/Types.h"

namespace gltut
{
//	Global classes

///	Represents a shader
class ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~ShaderParameters() noexcept = default;

	/// Returns the location of a shader parameter
	virtual int32 getParameterLocation(const char* name) const noexcept = 0;

	/// Sets an integer value to a shader parameter
	virtual void setInt(int32 location, int value) noexcept = 0;

	/// Sets a float value to a shader parameter
	virtual void setFloat(int32 location, float value) noexcept = 0;

	/// Sets a 2D vector to a shader parameter
	virtual void setVec2(int32 location, float x, float y) noexcept = 0;

	/// Sets a 3D vector to a shader parameter
	virtual void setVec3(int32 location, float x, float y, float z) noexcept = 0;

	/// Sets a 4D vector to a shader parameter
	virtual void setVec4(int32 location, float x, float y, float z, float w) noexcept = 0;

	/// Sets a 3x3 matrix to a shader parameter
	virtual void setMat3(int32 location, const float* data) noexcept = 0;

	/// Sets a 4x4 matrix to a shader parameter
	virtual void setMat4(int32 location, const float* data) noexcept = 0;

	/// Returns the location of a shader parameter, asserting that it exists
	int32 getParameterLocationChecked(const char* name) const noexcept
	{
		const int location = getParameterLocation(name);
		GLTUT_ASSERT(location != -1);
		return location;
	}

	/// Sets an integer value to a shader parameter
	void setInt(const char* name, int value) noexcept
	{
		setInt(getParameterLocationChecked(name), value);
	}

	/// Sets a float value to a shader parameter
	void setFloat(const char* name, float value) noexcept
	{
		setFloat(getParameterLocationChecked(name), value);
	}

	/// Sets a 2D vector to a shader parameter
	void setVec2(const char* name, float x, float y) noexcept
	{
		setVec2(getParameterLocationChecked(name), x, y);
	}

	/// Sets a 3D vector to a shader parameter
	void setVec3(const char* name, float x, float y, float z) noexcept
	{
		setVec3(getParameterLocationChecked(name), x, y, z);
	}

	/// Sets a 4D vector to a shader parameter
	void setVec4(const char* name, float x, float y, float z, float w) noexcept
	{
		setVec4(getParameterLocationChecked(name), x, y, z, w);
	}

	/// Sets a 3x3 matrix to a shader parameter
	void setMat3(const char* name, const float* data) noexcept
	{
		setMat3(getParameterLocationChecked(name), data);
	}

	/// Sets a 4x4 matrix to a shader parameter
	void setMat4(const char* name, const float* data) noexcept
	{
		setMat4(getParameterLocationChecked(name), data);
	}
};

// End of the namespace gltut
}
