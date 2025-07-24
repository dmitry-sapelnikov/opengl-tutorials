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

SceneC::SceneC(
	Window& window,
	RendererBase& renderer) :

	mWindow(window),
	mRenderer(renderer)
{
	// Set the background color
	mRenderer.setClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	// Get creation time in ms using high resolution clock
	mCreationTime = std::chrono::high_resolution_clock::now();
	mLastUpdateTime = mCreationTime;
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

Camera* SceneC::createCamera(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up,
	float fovDegrees,
	float nearPlane,
	float farPlan,
	const float* aspectRatio) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto* camera = &mCameras.emplace_back(
			mWindow,
			position,
			target,
			up,
			fovDegrees,
			nearPlane,
			farPlan,
			aspectRatio);

	if (mActiveCamera == nullptr)
	{
		mActiveCamera = camera;
	}
	return camera;
	GLTUT_CATCH_ALL_END("Cannot create a camera")

		return nullptr;
}

Camera* SceneC::getActiveCamera() const noexcept
{
	return mActiveCamera;
}

void SceneC::setActiveCamera(Camera* camera) noexcept
{
	mActiveCamera = camera;
}

void SceneC::addCameraController(CameraController* controller) noexcept
{
	GLTUT_ASSERT(controller != nullptr);
	GLTUT_CATCH_ALL_BEGIN
		mCameraControllers.push_back(controller);
	GLTUT_CATCH_ALL_END("Cannot add a camera controller")
}

void SceneC::removeCameraController(CameraController* controller) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		auto it = std::find(
			mCameraControllers.begin(),
			mCameraControllers.end(),
			controller);

		if (it != mCameraControllers.end())
		{
			mCameraControllers.erase(it);
		}
	GLTUT_CATCH_ALL_END("Cannot remove a camera controller")
}

void SceneC::update() noexcept
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - mCreationTime).count();

	const auto timeDeltaMs = static_cast<u32>(
		std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - mLastUpdateTime).count());

	if (timeDeltaMs == 0)
	{
		return;
	}

	for (auto* controller : mCameraControllers)
	{
		controller->updateCamera(timeMs, timeDeltaMs);
	}
	mLastUpdateTime = currentTime;
}

void SceneC::render() noexcept
{
	for (const auto& object : mObjects)
	{
		if (mActiveCamera != nullptr && 
			object.getMaterial() != nullptr && 
			object.getMaterial()->getShader() != nullptr)
		{
			auto* shader = object.getMaterial()->getShader();
			shader->activate();

			const auto& viewMatrix = mActiveCamera->getView().getMatrix();
			const auto& projectionMatrix = mActiveCamera->getProjection().getMatrix();

			if (const char* viewMatrixName = shader->getSceneParameterName(Shader::SceneParameter::VIEW);
				viewMatrixName != nullptr)
			{
				shader->setMat4(viewMatrixName, viewMatrix.data());
			}

			if (const char* projectionMatrixName = shader->getSceneParameterName(Shader::SceneParameter::PROJECTION);
				projectionMatrixName != nullptr)
			{
				shader->setMat4(projectionMatrixName, projectionMatrix.data());
			}

			if (const char* viewPositionName = shader->getSceneParameterName(Shader::SceneParameter::VIEW_POSITION);
				viewPositionName != nullptr)
			{
				const Vector3& viewPosition = mActiveCamera->getView().getPosition();
				shader->setVec3(viewPositionName, viewPosition.x, viewPosition.y, viewPosition.z);
			}
		}
		object.render();
	}
}

// End of the namespace gltut
}
