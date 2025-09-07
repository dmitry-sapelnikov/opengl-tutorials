// Includes
#include "MaterialFactoryC.h"
#include "../shader/FlatColorShader.h"
#include "../shader/DepthShader.h"

namespace gltut
{

MaterialFactoryC::MaterialFactoryC(
	Renderer& renderer,
	Scene& scene) noexcept :

	mRenderer(renderer),
	mScene(scene)
{
}

MaterialFactoryC::~MaterialFactoryC() noexcept
{
	auto* uniformBuffers = mRenderer.getDevice()->getShaderUniformBuffers();
	if (mViewProjectionBuffer != nullptr)
	{
		uniformBuffers->remove(mViewProjectionBuffer->getTarget());
		mRenderer.removeShaderUniformBufferBinding(mViewProjectionBuffer);
	}

	auto* shaders = mRenderer.getDevice()->getShaders();
	if (mFlatColorShader != nullptr)
	{
		shaders->remove(mFlatColorShader->getTarget());
		mRenderer.removeShaderBinding(mFlatColorShader);
	}

	if (mDepthShader != nullptr)
	{
		shaders->remove(mDepthShader->getTarget());
		mRenderer.removeShaderBinding(mDepthShader);
	}
}

FlatColorMaterialModel* MaterialFactoryC::createFlatColorMaterial(
	bool castShadows) noexcept
{
	FlatColorMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		createViewProjectionBuffer();
		createFlatColorShader();
		if (castShadows)
		{
			createDepthShader();
		}
		result = &mFlatColorModels.emplace_back(
			mRenderer,
			*mFlatColorShader,
			castShadows ? mDepthShader : nullptr,
			*mViewProjectionBuffer->getTarget());
	GLTUT_CATCH_ALL_END("Cannot create a flat color material model")
	return result;
}

PhongShaderModel* MaterialFactoryC::createPhongShader(
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept
{
	PhongShaderModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		createViewProjectionBuffer();
		result = &mPhongShaders.emplace_back(
			mRenderer,
			mScene,
			maxDirectionalLights,
			maxPointLights,
			maxSpotLights);
	GLTUT_CATCH_ALL_END("Cannot create a Phong shader")
	return result;
}

PhongMaterialModel* MaterialFactoryC::createPhongMaterial(
	const PhongShaderModel* phongShader,
	bool castShadows) noexcept
{
	if (!GLTUT_ASSERT(phongShader != nullptr) ||
		!GLTUT_ASSERT(mViewProjectionBuffer != nullptr))
	{
		return nullptr;
	}

	PhongMaterialModel* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (castShadows)
		{
			createDepthShader();
		}
		result = &mPhongModels.emplace_back(
			mRenderer,
			mScene,
			*phongShader,
			castShadows ? mDepthShader : nullptr,
			*mViewProjectionBuffer->getTarget());
	GLTUT_CATCH_ALL_END("Cannot create a Phong material model")
	return result;
}

void MaterialFactoryC::createViewProjectionBuffer()
{
	static_assert(sizeof(Matrix4) == 16 * sizeof(float));

	if (mViewProjectionBuffer == nullptr)
	{
		auto* buffer = mRenderer.getDevice()->getShaderUniformBuffers()->create(sizeof(Matrix4) * 2);
		GLTUT_CHECK(
			buffer != nullptr,
			"Failed to create view projection uniform buffer");

		mViewProjectionBuffer = mRenderer.createShaderUniformBufferBinding(buffer);
		GLTUT_CHECK(
			mViewProjectionBuffer != nullptr,
			"Failed to create view projection uniform buffer binding");

		mViewProjectionBuffer->bind(RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX, 0);
		mViewProjectionBuffer->bind(RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX, sizeof(Matrix4));
	}
}

void MaterialFactoryC::createFlatColorShader()
{
	if (mFlatColorShader == nullptr)
	{
		mFlatColorShader = gltut::createFlatColorShader(mRenderer);
		GLTUT_CHECK(
			mFlatColorShader != nullptr,
			"Failed to create flat color shader");
	}
}

void MaterialFactoryC::createDepthShader()
{
	if (mDepthShader == nullptr)
	{
		mDepthShader = gltut::createDepthShader(mRenderer);
		GLTUT_CHECK(
			mDepthShader != nullptr,
			"Failed to create depth shader");
	}
}

void MaterialFactoryC::update() noexcept
{
}

// End of the namespace gltut
}
