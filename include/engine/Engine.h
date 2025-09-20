// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/factory/Factory.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/window/Window.h"

namespace gltut
{
// Global classes
/**
	\brief The main engine interface.
	Provides access to the window, device, scene, renderer and factories.
*/
class Engine
{
public:
	/// Virtual destructor
	virtual ~Engine() noexcept = default;

	/**
		\brief Performs a single update of the engine
		\return true if the update was successful, false otherwise
	*/
	virtual bool update() noexcept = 0;

	/// Returns the window
	virtual Window* getWindow() noexcept = 0;

	/// Returns the device
	virtual GraphicsDevice* getDevice() noexcept = 0;

	/// Returns the scene
	virtual Scene* getScene() noexcept = 0;

	/// Returns the render pipeline
	virtual Renderer* getRenderer() noexcept = 0;

	/// Returns the geometry factory
	virtual Factory* getFactory() noexcept = 0;

	/// Return the scene render pass
	virtual RenderPass* getSceneRenderPass() noexcept = 0;

	/// Return the depth-sorted scene render pass
	virtual RenderPass* getDepthSortedSceneRenderPass() noexcept = 0;
};

// Global functions
/**
	\brief Creates the engine instance
	\return The engine if it was created successfully, nullptr otherwise
	\note The caller is responsible for deleting the instance
*/
Engine* createEngine(u32 windowWidth, u32 windowHeight) noexcept;

/// \todo Add deleteEngine function

// End of the namespace gltut
}
