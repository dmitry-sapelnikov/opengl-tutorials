#pragma once

// Includes
#include "SceneRenderPassC.h"

namespace gltut
{
//	Global classes
SceneRenderPassC::SceneRenderPassC(
	Renderer& renderer,
	Framebuffer* target,
	const Color& clearColor,
	Scene& scene,
	const Viewpoint* viewpoint,
	u32 materialPass) noexcept :

	RenderPassT<SceneRenderPass>(renderer, target, clearColor),
	mScene(scene),
	mViewpoint(viewpoint),
	mMaterialPass(materialPass)
{
}

void SceneRenderPassC::doExecute() noexcept
{
	for (u32 i = 0; i < mScene.getShaderBindingCount(); ++i)
	{
		mScene.getShaderBinding(i)->update(mViewpoint);
	}

	for (u32 i = 0; i < mScene.getGeometryCount(); ++i)
	{
		GeometryNode* geometry = mScene.getGeometry(i);
		if (geometry->getMesh() != nullptr &&
			geometry->getMaterial() != nullptr)
		{
			if (const MaterialPass* materialPass = (*geometry->getMaterial())[mMaterialPass];
				materialPass != nullptr)
			{
				materialPass->activate(geometry);
				geometry->getMesh()->render();
			}
		}
	}
}

// End of the namespace gltut
}
