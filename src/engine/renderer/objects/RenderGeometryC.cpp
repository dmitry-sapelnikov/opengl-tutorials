// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "RenderGeometryC.h"

namespace gltut
{
// Global classes
void RenderGeometryC::render(u32 materialPass) const noexcept
{
	if (mMaterial != nullptr &&
		mMaterial->getPass(materialPass) != nullptr &&
		mGeometry != nullptr)
	{
		mMaterial->getPass(materialPass)->bind(this);
		mGeometry->render();
	}
}

// End of the namespace gltut
}
