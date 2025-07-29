// Includes
#include "PhongMaterialModelC.h"


namespace gltut
{
// Global classes
PhongMaterialModelC::PhongMaterialModelC(Material& material) noexcept :
	mMaterial(material)
{
}

void PhongMaterialModelC::setAmbient(Texture* ambient) noexcept
{
	mMaterial.setTexture(ambient, 0);
}

void PhongMaterialModelC::setDiffuse(Texture* diffuse) noexcept
{
	mMaterial.setTexture(diffuse, 1);
}

void PhongMaterialModelC::setSpecular(Texture* specular) noexcept
{
	mMaterial.setTexture(specular, 2);
}

void PhongMaterialModelC::setShininess(float shininess) noexcept
{
	mMaterial.getShaderArguments()->setFloat("shininess", shininess);
}

// End of the namespace gltut
}
