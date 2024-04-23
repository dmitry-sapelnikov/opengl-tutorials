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

SceneC::SceneC(RendererBase& renderer) :
	mRenderer(renderer)
{
	// Set the background color
	mRenderer.setClearColor(0.1f, 0.3f, 0.3f, 1.0f);
}

Material* SceneC::createMaterial(Shader* shader) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
	return &mMaterials.emplace_back(shader);
	GLTUT_CATCH_ALL_END("Cannot create a material")
	return nullptr;
}

Mesh* SceneC::createMesh(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertexData,
	u32 indexCount,
	const u32* indexData) noexcept
{
	try
	{
		return &mMeshes.emplace_back(
			mRenderer,
			vertexFormat,
			vertexCount,
			vertexData,
			indexCount,
			indexData);
	}
	catch (...)
	{
		return nullptr;
	}
}

SceneObject* SceneC::createObject(
	Mesh* mesh,
	Material* material,
	const Matrix4& transform) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
	return &mObjects.emplace_back(mRenderer, mesh, material, transform);
	GLTUT_CATCH_ALL_END("Cannot create a scene object")
	return nullptr;
}

void SceneC::render() noexcept
{
	for (const auto& object : mObjects)
	{
		object.render();
	}
}

// End of the namespace gltut
}
