// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "ShaderRendererBindingC.h"
#include "engine/renderer/Renderer.h"

namespace gltut
{
// Global classes
void ShaderRendererBindingC::update(const Viewpoint* viewpoint, float aspectRatio) const noexcept
{
	Shader* shader = getTarget();

	if (shader == nullptr || viewpoint == nullptr)
	{
		return;
	}

	if (const char* cameraView = getBoundShaderParameter(RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX);
		cameraView != nullptr)
	{
		shader->setMat4(cameraView, viewpoint->getViewMatrix().data());
	}

	if (const char* cameraProjection = getBoundShaderParameter(RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX);
		cameraProjection != nullptr)
	{
		shader->setMat4(cameraProjection, viewpoint->getProjectionMatrix(aspectRatio).data());
	}

	if (const char* cameraPosition = getBoundShaderParameter(RendererBinding::Parameter::VIEWPOINT_POSITION);
		cameraPosition != nullptr)
	{
		const Vector3 position = viewpoint->getPosition();
		shader->setVec3(cameraPosition, position.x, position.y, position.z);
	}
}

void ShaderRendererBindingC::update(const RenderGeometry* geometry) const noexcept
{
	Shader* shader = getTarget();
	if (shader == nullptr || geometry == nullptr)
	{
		return;
	}

	if (const char* objectMatrix = getBoundShaderParameter(RendererBinding::Parameter::GEOMETRY_MATRIX);
		objectMatrix != nullptr)
	{
		shader->setMat4(objectMatrix, geometry->getTransform().data());
	}

	if (const char* objectNormalMatrix = getBoundShaderParameter(RendererBinding::Parameter::GEOMETRY_NORMAL_MATRIX);
		objectNormalMatrix != nullptr)
	{
		const Matrix3 normalMatrix = getNormalMatrix(geometry->getTransform().getMatrix3());
		shader->setMat3(objectNormalMatrix, normalMatrix.data());
	}
}

// Global functions
ShaderRendererBinding* createStandardShaderBinding(
	Renderer* renderer,
	const char* vertexShaderSource,
	const char* fragmentShaderSource,
	const char* modelMatrixName,
	const char* viewMatrixName,
	const char* projectionMatrixName,
	const char* normalMatrixName) noexcept
{
	GLTUT_ASSERT(renderer != nullptr);
	GLTUT_ASSERT(vertexShaderSource != nullptr);
	GLTUT_ASSERT(fragmentShaderSource != nullptr);

	if (renderer == nullptr ||
		vertexShaderSource == nullptr ||
		fragmentShaderSource == nullptr)
	{
		return nullptr;
	}

	GraphicsDevice* device = renderer->getDevice();
	Shader* shader = device->getShaders()->create(
		vertexShaderSource,
		fragmentShaderSource);

	if (shader == nullptr)
	{
		return nullptr;
	}

	ShaderRendererBinding* result = renderer->createShaderBinding(shader);

	if (result == nullptr)
	{
		device->getShaders()->remove(shader);
		return nullptr;
	}

	if (modelMatrixName != nullptr)
	{
		result->bind(RendererBinding::Parameter::GEOMETRY_MATRIX, modelMatrixName);
	}

	if (viewMatrixName != nullptr)
	{
		result->bind(RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX, viewMatrixName);
	}

	if (projectionMatrixName != nullptr)
	{
		result->bind(RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX, projectionMatrixName);
	}

	if (normalMatrixName != nullptr)
	{
		result->bind(RendererBinding::Parameter::GEOMETRY_NORMAL_MATRIX, normalMatrixName);
	}

	return result;
}

// End of the namespace gltut
}
