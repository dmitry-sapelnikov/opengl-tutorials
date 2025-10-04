// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "FactoryC.h"

namespace gltut
{
// Global classes
FactoryC::FactoryC(
	Renderer& renderer,
	Scene& scene,
	Window& window) noexcept :

	mGeometry(*renderer.getDevice()),
	mMaterial(renderer, scene),
	mRenderPass(renderer),
	mTexture(*renderer.getDevice(), window),
	mScene(renderer, mGeometry)
{
}

// End of the namespace gltut
}
