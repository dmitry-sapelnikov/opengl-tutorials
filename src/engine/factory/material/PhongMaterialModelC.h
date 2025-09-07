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
		const PhongShaderModel& phongShader,
		ShaderRendererBinding* depthShader,
		const ShaderUniformBuffer& viewProjectionBuffer);

	/// Virtual destructor
	~PhongMaterialModelC() noexcept final;

	// Returns the Phong shader model
	const PhongShaderModel* getPhongShader() const noexcept final
	{
		return &mPhongShader;
	}

	// Sets the diffuse texture
	void setDiffuse(const Texture* diffuse) noexcept final;

	// Sets the specular texture
	void setSpecular(const Texture* specular) noexcept final;

	// Sets the normal texture
	void setNormal(const Texture* normal) noexcept final;

	// Sets the height texture
	void setDepth(const Texture* height) noexcept final;

	// Sets the height scale
	void setDepthtScale(float depthScale) noexcept final;

	// Sets the shininess value
	void setShininess(float shininess) noexcept final;

private:
	/// The scene
	Scene& mScene;

	/// The Phong shader model
	const PhongShaderModel& mPhongShader;

	/// The texture set binding
	SceneTextureSetBinding* mTextureSetBinding = nullptr;
};

// End of the namespace gltut
}
