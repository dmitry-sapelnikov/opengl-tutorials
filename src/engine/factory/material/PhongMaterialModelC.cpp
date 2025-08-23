// Includes
#include "PhongMaterialModelC.h"
#include "engine/factory/material/MaterialPassIndex.h"

namespace gltut
{
// Global classes
PhongMaterialModelC::PhongMaterialModelC(
	Renderer& renderer,
	Scene& scene,
	PhongShaderModel& phongShader,
	ShaderRendererBinding* depthShader) :

	MaterialModelT<PhongMaterialModel>(renderer),
	mScene(scene),
	mPhongShader(phongShader)
{
	MaterialPass* lightingPass = getMaterial().createPass(
		static_cast<u32>(MaterialPassIndex::LIGHTING),
		phongShader.getShader(),
		PhongShaderModel::TEXTURE_SLOTS_COUNT + 
		phongShader.getMaxDirectionalLights() + 
		phongShader.getMaxSpotLights());
	GLTUT_CHECK(lightingPass != nullptr, "Failed to create a material pass");

	if (depthShader != nullptr)
	{
		MaterialPass* depthPass = getMaterial().createPass(
			static_cast<u32>(MaterialPassIndex::DEPTH),
			depthShader,
			PhongShaderModel::TEXTURE_SLOTS_COUNT + 
			phongShader.getMaxDirectionalLights() +
			phongShader.getMaxSpotLights());

		GLTUT_CHECK(
			depthPass != nullptr,
			"Failed to create the depth pass for the Phong material model");
	}

	mTextureSetBinding = mScene.createTextureSetBinding(lightingPass->getTextures());
	GLTUT_CHECK(mTextureSetBinding != nullptr, "Failed to create a texture set binding");
	
	mTextureSetBinding->bind(
		SceneTextureSetBinding::Parameter::DIRECTIONAL_LIGHT_SHADOW_MAP,
		PhongShaderModel::TEXTURE_SLOTS_COUNT);

	mTextureSetBinding->bind(
		SceneTextureSetBinding::Parameter::SPOT_LIGHT_SHADOW_MAP,
		PhongShaderModel::TEXTURE_SLOTS_COUNT + phongShader.getMaxDirectionalLights());
}

PhongMaterialModelC::~PhongMaterialModelC() noexcept
{
	mScene.removeTextureSetBinding(mTextureSetBinding);
}

void PhongMaterialModelC::setDiffuse(const Texture* diffuse) noexcept
{
	getMaterial()[0]->getTextures()->setTexture(diffuse, 0);
}

void PhongMaterialModelC::setSpecular(const Texture* specular) noexcept
{
	getMaterial()[0]->getTextures()->setTexture(specular, 1);
}

void PhongMaterialModelC::setNormal(const Texture* normal) noexcept
{
	getMaterial()[0]->getTextures()->setTexture(normal, 2);
}

void PhongMaterialModelC::setShininess(float shininess) noexcept
{
	getMaterial()[0]->getShaderArguments()->setFloat("shininess", shininess);
}

// End of the namespace gltut
}
