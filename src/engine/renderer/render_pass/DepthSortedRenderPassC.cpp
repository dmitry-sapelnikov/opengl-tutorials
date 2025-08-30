// Includes
#include "DepthSortedRenderPassC.h"

namespace gltut
{

//	Global classes
DepthSortedRenderPassC::DepthSortedRenderPassC(
	const Viewpoint* viewpoint,
	const RenderGeometryGroup* group,
	Framebuffer* target,
	u32 materialPass,
	const Color* clearColor,
	bool clearDepth,
	const Rectangle2u* viewport,
	bool cullBack,
	bool cullFront,
	bool enableBlending,
	GraphicsDevice& device,
	const ShaderBindings& shaderBindings) noexcept :

	RenderPassC(
		viewpoint,
		group,
		target,
		materialPass,
		clearColor,
		clearDepth,
		viewport,
		cullBack,
		cullFront,
		enableBlending,
		device,
		shaderBindings),

	mGroup(group)
{
}

void DepthSortedRenderPassC::execute() noexcept
{
	const Matrix4 viewMatrix = getViewpoint()->getViewMatrix();
	if (!(mViewMatrix - viewMatrix).isNearZero())
	{
		mViewMatrix = viewMatrix;
		mSortedGroup.clear();
		for (u32 i = 0; i < mGroup->getSize(); ++i)
		{
			mSortedGroup.add(mGroup->get(i));
		}

		std::sort(
			mSortedGroup.begin(),
			mSortedGroup.end(),
			[&viewMatrix](const RenderGeometry* a, const RenderGeometry* b)
			{
				const Vector3 aPos = a->getTransform().getTranslation();
				const Vector3 bPos = b->getTransform().getTranslation();
				// The further the object, the smaller the z value in view space
				return (viewMatrix * aPos).z < (viewMatrix * bPos).z;
			});
	}
	RenderPassC::execute(&mSortedGroup);
}

// End of the namespace gltut
}
