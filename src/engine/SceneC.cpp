// Includes
#include "SceneC.h"
#include <stdexcept>
#include "MeshC.h"

namespace
{
// Vertex shader source code
const char* VERTEX_SHADER_SOURCE_CODE =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"}";

// Fragment shader source code
const char* FRAGMENT_SHADER_SOURCE_CODE =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";
}

namespace gltut
{

SceneC::SceneC(Renderer& renderer) :
	mRenderer(renderer)
{
	// Set the background color
	mRenderer.setClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	mShaderProgram = mRenderer.createShaderProgram(
		VERTEX_SHADER_SOURCE_CODE,
		FRAGMENT_SHADER_SOURCE_CODE);

	if (!mShaderProgram)
	{
		throw std::runtime_error("Failed to create the shader program");
	}
}

SceneC::~SceneC() noexcept
{
	mRenderer.freeShaderProgram(mShaderProgram);
}

Mesh* SceneC::createMesh(
	float* vertices,
	u32 vertexCount,
	u32* indices,
	u32 indexCount) noexcept
{
	try
	{
		return &mMeshes.emplace_back(
			mRenderer,
			vertices,
			vertexCount,
			indices,
			indexCount);
	}
	catch (...)
	{
		return nullptr;
	}
}

void SceneC::render() noexcept
{
	mRenderer.clear();
	mRenderer.setShaderProgram(mShaderProgram);
	for (const auto& mesh : mMeshes)
	{
		mesh.render();
	}
}

// End of the namespace gltut
}
