#pragma once

// Includes
#include "engine/scene/nodes/GeometryNode.h"
#include "engine/factory/shader/PhongShaderModel.h"
#include "engine/factory/material/MaterialFactory.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global classes
/// The scene factory interface. Creates various scene nodes.
class SceneFactory
{
public:
	/**
		\brief Loads a geometry node and its children from a file
		\return The geometry node if it was loaded successfully, nullptr otherwise
	*/
	virtual SceneNode* loadModel(
		const char* filePath,
		PhongShaderModel* phongShader) noexcept = 0;
};

SceneFactory* createSceneFactory(
	GraphicsDevice& device,
	Scene& scene,
	MaterialFactory& materialFactory) noexcept;

void deleteSceneFactory(SceneFactory* factory) noexcept;

// End of the namespace gltut
}
