// Includes

#include "StandardShaderBinding.h"

namespace gltut
{
// Global functions
ShaderRendererBinding* createStandardShaderBinding(
	Renderer& renderer,
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	Shader* shader = nullptr;
	ShaderRendererBinding* result = nullptr;

	GLTUT_CATCH_ALL_BEGIN
		Shader* shader = renderer.getDevice()->getShaders()->create(
			vertexShader,
			fragmentShader);

		GLTUT_CHECK(shader != nullptr, "Cannot create a material shader");

		result = renderer.createShaderBinding(shader);
		GLTUT_CHECK(result != nullptr, "Cannot create a shader renderer binding");

		result->bind(RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX, "view");
		result->bind(RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX, "projection");
		result->bind(RendererBinding::Parameter::GEOMETRY_MATRIX, "model");

		return result;
	GLTUT_CATCH_ALL_END("Cannot create a material shader");

	renderer.removeShaderBinding(result);
	renderer.getDevice()->getShaders()->remove(shader);
	return nullptr;
}

// End of the namespace gltut
}
