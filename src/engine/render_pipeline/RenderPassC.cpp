#pragma once

// Includes
#include "RenderPassC.h"

namespace gltut
{
//	Global classes
RenderPassC::RenderPassC(
	Renderer& renderer,
	Scene& scene,
	Framebuffer* target,
	const Viewpoint* viewer,
	const Color& clearColor,
	u32 materialPass) noexcept :

	mRenderer(renderer),
	mScene(scene),
	mTarget(target),
	mViewpoint(viewer),
	mClearColor(clearColor),
	mMaterialPass(materialPass)
{
}

void RenderPassC::execute() noexcept
{
	mRenderer.activateFramebuffer(mTarget);
	mRenderer.clear(mClearColor);

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
