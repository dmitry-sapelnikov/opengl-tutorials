// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "asset_loader/AssetLoader.h"
#include "engine/core/NonCopyable.h"

namespace gltut
{
// Global classes
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
		const AssetMaterialFactory* materialCreator,
		bool loadTextures) noexcept final;

private:
	/// Vector of materials
	using MaterialsType = std::vector<const Material*>;

	/// Loads a texture from a material
	Texture2* loadMaterialTexture(
		const std::string& modelDirectory,
		aiMaterial* mat,
		aiTextureType type);

	/// Creates materials from a scene
	MaterialsType createMaterials(
		const std::string& modelDirectory,
		const aiScene& scene,
		const AssetMaterialFactory& materialCreator,
		bool loadTextures);

	/// Creates a geometry from an aiMesh
	Geometry* createGeometry(aiMesh* mesh);

	/// Processes meshes from a scene
	void processMeshes(
		const aiScene& scene,
		const MaterialsType& materials,
		std::vector<Geometry*>& geometries,
		MaterialsType& geometryMaterials);

	/// Creates a compound geometry node from an aiNode
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
