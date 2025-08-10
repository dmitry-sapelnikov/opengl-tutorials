// Includes
#include "PhongMaterialModelC.h"

namespace gltut
{
// Global classes
PhongMaterialModelC::PhongMaterialModelC(
	Renderer& renderer,
	Scene& scene,
	PhongShaderModel& phongShader) :

	MaterialModelT<PhongMaterialModel>(renderer),
	mScene(scene),
	mPhongShader(phongShader)
{
	MaterialPass* materialPass = getMaterial().createPass(
		0,
		phongShader.getMaterialBinding(),
		PhongShaderModel::TEXTURE_SLOTS_COUNT + phongShader.getMaxDirectionalLights());
	GLTUT_CHECK(materialPass != nullptr, "Failed to create a material pass");

	mTextureSetBinding = mScene.createTextureSetBinding(materialPass->getTextures());
	GLTUT_CHECK(mTextureSetBinding != nullptr, "Failed to create a texture set binding");
	
	mTextureSetBinding->bind(
		SceneTextureSetBinding::Parameter::DIRECTIONAL_LIGHT_SHADOW_MAP,
		PhongShaderModel::TEXTURE_SLOTS_COUNT);
}

PhongMaterialModelC::~PhongMaterialModelC() noexcept
{
	mScene.removeTextureSetBinding(mTextureSetBinding);
}

void PhongMaterialModelC::setDiffuse(Texture* diffuse) noexcept
{
	getMaterial()[0]->getTextures()->setTexture(diffuse, 0);
}

void PhongMaterialModelC::setSpecular(Texture* specular) noexcept
{
	getMaterial()[0]->getTextures()->setTexture(specular, 1);
}

void PhongMaterialModelC::setShininess(float shininess) noexcept
{
	getMaterial()[0]->getShaderArguments()->setFloat("shininess", shininess);
}

// End of the namespace gltut
}
