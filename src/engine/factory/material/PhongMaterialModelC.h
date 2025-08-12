#pragma once

// Includes
#include "engine/factory/material/PhongMaterialModel.h"
#include "engine/scene/Scene.h"
#include "./MaterialModelT.h"

namespace gltut
{
// Global classes
/// Implementation of the PhongMaterialModel interface
class PhongMaterialModelC final : public MaterialModelT<PhongMaterialModel>
{
public:
	/// Constructor
	PhongMaterialModelC(
		Renderer& renderer,
		Scene& scene,
		PhongShaderModel& phongShader,
		ShaderRendererBinding* depthShader);

	/// Virtual destructor
	~PhongMaterialModelC() noexcept final;

	// Returns the Phong shader model
	PhongShaderModel* getPhongShader() const noexcept final
	{
		return &mPhongShader;
	}

	// Sets the diffuse texture
	void setDiffuse(Texture* diffuse) noexcept final;

	// Sets the specular texture
	void setSpecular(Texture* specular) noexcept final;

	// Sets the shininess value
	void setShininess(float shininess) noexcept final;

private:
	/// The scene
	Scene& mScene;

	/// The Phong shader model
	PhongShaderModel& mPhongShader;

	/// The texture set binding
	SceneTextureSetBinding* mTextureSetBinding = nullptr;
};

// End of the namespace gltut
}
