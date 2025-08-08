#pragma once

// Includes
#include "RenderGeometryC.h"

namespace gltut
{
//	Global classes
void RenderGeometryC::render(u32 materialPass) const noexcept
{
	if (mMaterial != nullptr &&
		mMaterial->getPass(materialPass) != nullptr)
	{
		mMaterial->getPass(materialPass)->bind(this);
	}

	if (mGeometry != nullptr)
	{
		mGeometry->render();
	}
}

// End of the namespace gltut
}
