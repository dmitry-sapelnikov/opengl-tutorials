#pragma once

// Includes
#include "engine/graphics/Shader/ShaderManager.h"
#include "../../core/ItemManagerT.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the ShaderManager interface
class ShaderManagerC : public ItemManagerT<ShaderManager>
{
public:
	/// Constructor
	ShaderManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a shader from strings
	Shader* create(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Creates a shader from files
	Shader* load(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
