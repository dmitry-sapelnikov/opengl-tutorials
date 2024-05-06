// Includes
#include "ShaderC.h"
#include "engine/core/Check.h"

namespace gltut
{

void ShaderC::setModelMatrixName(const char* name) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		mModelMatrixName = name;
	GLTUT_CATCH_ALL_END("Setting of the model matrix name failed")
}

void ShaderC::setViewMatrixName(const char* name) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		mViewMatrixName = name;
	GLTUT_CATCH_ALL_END("Setting of the view matrix name failed")
}

void ShaderC::setProjectionMatrixName(const char* name) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		mProjectionMatrixName = name;
	GLTUT_CATCH_ALL_END("Setting of the projection matrix name failed")
}

void ShaderC::setNormalMatrixName(const char* name) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		mNormalMatrixName = name;
	GLTUT_CATCH_ALL_END("Setting of the normal matrix name failed")
}

// End of the namespace gltut
}
