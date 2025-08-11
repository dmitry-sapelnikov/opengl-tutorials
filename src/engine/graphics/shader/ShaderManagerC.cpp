// Includes
#include "ShaderManagerC.h"
#include "../../core/File.h"
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
Shader* ShaderManagerC::create(
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	Shader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendShader(
			vertexShader,
			fragmentShader));
	GLTUT_CATCH_ALL_END("Failed to create shader program")
	return result;
}

Shader* ShaderManagerC::load(
	const char* vertexShaderPath,
	const char* fragmentShaderPath) noexcept
{
	Shader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendShader(
			readFileToString(vertexShaderPath).c_str(),
			readFileToString(fragmentShaderPath).c_str()));
	GLTUT_CATCH_ALL_END("Failed to load shader from files")
		return result;
}

// End of the namespace gltut
}
