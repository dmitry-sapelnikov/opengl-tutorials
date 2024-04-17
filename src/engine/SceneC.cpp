// Includes
#include "SceneC.h"

#include <stdexcept>
#include "engine/core/Check.h"
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
"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
"}";
}

namespace gltut
{

SceneC::SceneC(Renderer& renderer) :
	mRenderer(renderer)
{
	mDefaultShader = mRenderer.createShader(
		VERTEX_SHADER_SOURCE_CODE,
		FRAGMENT_SHADER_SOURCE_CODE);

	GLTUT_CHECK(mDefaultShader != nullptr, "Failed to create the default scene shader");

	// Set the background color
	mRenderer.setClearColor(0.1f, 0.3f, 0.3f, 1.0f);
}

SceneC::~SceneC() noexcept
{
	mRenderer.removeShader(mDefaultShader);
}

Mesh* SceneC::createMesh(
	VertexFormat vertexFormat,
	float* vertices,
	u32 vertexCount,
	u32* indices,
	u32 indexCount) noexcept
{
	try
	{
		return &mMeshes.emplace_back(
			mRenderer,
			vertexFormat,
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
	for (const auto& mesh : mMeshes)
	{
		mDefaultShader->use();
		mesh.render();
	}
}

// End of the namespace gltut
}
