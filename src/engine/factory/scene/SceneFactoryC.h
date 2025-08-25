#pragma once

// Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "engine/core/NonCopyable.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/MaterialFactory.h"
#include "engine/factory/scene/SceneFactory.h"

namespace gltut
{

/// Implementation of the SceneFactory class
class SceneFactoryC final : public SceneFactory, public NonCopyable
{
public:
	// Constructor
	SceneFactoryC(
		GraphicsDevice& device,
		Scene& scene,
		MaterialFactory& materialFactory);

	/**
		\brief Loads a geometry node and its children from a file
		\return The geometry node if it was loaded successfully, nullptr otherwise
	*/
	SceneNode* loadModel(
		const char* filePath,
		PhongShaderModel* phongShader) noexcept final;

private:
	Texture* loadMaterialTexture(
		const std::string& modelDirectory,
		aiMaterial* mat,
		aiTextureType type);

	std::vector<PhongMaterialModel*> createMaterials(
		const std::string& modelDirectory,
		const aiScene& scene,
		const PhongShaderModel& phongShader);

	Geometry* createGeometry(aiMesh* mesh);

	void processMeshes(
		const aiScene& scene,
		const std::vector<PhongMaterialModel*>& materials,
		std::vector<Geometry*>& geometries,
		std::vector<PhongMaterialModel*>& geometryMaterials);

	SceneNode* createCompoundGeometryNode(
		aiNode* node,
		SceneNode* parent,
		const std::vector<Geometry*>& geometries,
		const std::vector<PhongMaterialModel*>& geometryMaterials);

	/// The graphics device used to create resources
	GraphicsDevice& mDevice;

	/// The target scene
	Scene& mScene;

	/// The material factory used to create the materials
	MaterialFactory& mMaterialFactory;
};

// End of the namespace gltut
}
