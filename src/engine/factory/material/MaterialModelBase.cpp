// Includes
#include "PhongMaterialModelC.h"


namespace gltut
{
// Global classes
PhongMaterialModelC::PhongMaterialModelC(Material& material) noexcept :
	mMaterial(material)
{
}

const Material* PhongMaterialModelC::getMaterial() const noexcept
{
	return &mMaterial;
}

void PhongMaterialModelC::setDiffuse(Texture* diffuse) noexcept
{
	mMaterial.setTexture(diffuse, 0);
}

void PhongMaterialModelC::setSpecular(Texture* specular) noexcept
{
	mMaterial.setTexture(specular, 1);
}

void PhongMaterialModelC::setShininess(float shininess) noexcept
{
	mMaterial.getShaderArguments()->setFloat("shininess", shininess);
}

// End of the namespace gltut
}
