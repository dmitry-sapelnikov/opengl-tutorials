// Includes
#include "DepthSortedRenderPassC.h"

namespace gltut
{

// Local classes
namespace
{
class DepthSorter final : public RenderGroup::Sorter
{
public:
	explicit DepthSorter(const Matrix4& viewpointMatrix) noexcept :
		mViewpointMatrix(viewpointMatrix)
	{
	}

	bool operator()(
		const RenderObject* a,
		const RenderObject* b) const noexcept final
	{
		/*const Vector3 posA = a->getTransform().getTranslation();
		const Vector3 posB = b->getTransform().getTranslation();

		Vector4 viewPosA = mViewpointMatrix * Vector4(posA, 1.0f);
		viewPosA /= viewPosA.w;

		Vector4 viewPosB = mViewpointMatrix * Vector4(posB, 1.0f);
		viewPosB /= viewPosB.w;

		return viewPosA.z > viewPosB.z;*/
		return false;
	}

private:
	Matrix4 mViewpointMatrix;
};

// end of the anonymous namespace
}

//	Global classes
DepthSortedRenderPassC::DepthSortedRenderPassC(
	const Viewpoint* viewpoint,
	RenderGroup* group,
	Framebuffer* target,
	u32 materialPass,
	const Color* clearColor,
	bool clearDepth,
	const Rectangle2u* viewport,
	bool cullBack,
	bool cullFront,
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
		device,
		shaderBindings),
	mGroup(group)
{
}

void DepthSortedRenderPassC::execute() noexcept
{
	const float aspectRatio = getViewport() != nullptr ?
		static_cast<float>(getViewport()->getSize().x) /
		static_cast<float>(getViewport()->getSize().y) :
		1.0f;

	const Matrix4 viewpointMatrix = 
		getViewpoint()->getProjectionMatrix(aspectRatio) *
		getViewpoint()->getViewMatrix();

	if (!(mViewpointMatrix - viewpointMatrix).isNearZero())
	{
		mViewpointMatrix = viewpointMatrix;
		DepthSorter depthSorter(mViewpointMatrix);
		mGroup->sort(&depthSorter);
	}

	RenderPassC::execute();
}

// End of the namespace gltut
}
