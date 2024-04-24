#ifndef OPENGL_TUTORIALS_SHADER_C_H
#define OPENGL_TUTORIALS_SHADER_C_H

// Includes
#include <string>
#include "engine/Shader.h"
#include "engine/core/NonCopyable.h"

namespace gltut
{

class ShaderC : public Shader, public NonCopyable
{
public:
	const char* getModelMatrixName() const noexcept final
	{
		return mModelMatrixName.empty() ? nullptr : mModelMatrixName.c_str();
	}

	void setModelMatrixName(const char* name) noexcept final;

	const char* getViewMatrixName() const noexcept final
	{
		return mViewMatrixName.empty() ? nullptr : mViewMatrixName.c_str();
	}

	void setViewMatrixName(const char* name) noexcept final;

	const char* getProjectionMatrixName() const noexcept final
	{
		return mProjectionMatrixName.empty() ? nullptr : mProjectionMatrixName.c_str();
	}

	void setProjectionMatrixName(const char* name) noexcept final;

private:
	/// The model matrix name
	std::string mModelMatrixName;

	/// The view matrix name
	std::string mViewMatrixName;

	/// The projection matrix name
	std::string mProjectionMatrixName;
};

// End of the namespace gltut
}

#endif
