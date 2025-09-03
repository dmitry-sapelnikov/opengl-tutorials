#pragma once

// Includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "engine/core/NonCopyable.h"
#include "asset_loader/AssetLoader.h"

namespace gltut
{

/// Implementation of the AssetLoader class
class AssetLoaderC final : public AssetLoader, public NonCopyable
{
public:
	// Constructor
	explicit AssetLoaderC(Engine& engine) noexcept;

	/**
		\brief Loads a geometry node and its children from a file
		\return The geometry node if it was loaded successfully, nullptr otherwise
	*/
	SceneNode* loadAsset(
		const char* filePath,
		const AssetMaterialFactory* materialCreator) noexcept final;

private:
	/// Vector of materials
	using MaterialsType = std::vector<const Material*>;

	Texture2* loadMaterialTexture(
		const std::string& modelDirectory,
		aiMaterial* mat,
		aiTextureType type);

	MaterialsType createMaterials(
		const std::string& modelDirectory,
		const aiScene& scene,
		const AssetMaterialFactory& materialCreator);

	Geometry* createGeometry(aiMesh* mesh);

	void processMeshes(
		const aiScene& scene,
		const MaterialsType& materials,
		std::vector<Geometry*>& geometries,
		MaterialsType& geometryMaterials);

	SceneNode* createCompoundGeometryNode(
		aiNode* node,
		SceneNode* parent,
		const std::vector<Geometry*>& geometries,
		const MaterialsType& geometryMaterials);

	/// Reference to the engine
	Engine& mEngine;
};

// End of the namespace gltut
}
