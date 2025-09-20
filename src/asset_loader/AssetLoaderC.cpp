// Includes
#include "AssetLoaderC.h"
#include <filesystem>

namespace gltut
{

// Global classes
AssetLoaderC::AssetLoaderC(Engine& engine) noexcept :
	mEngine(engine)
{
}

SceneNode* AssetLoaderC::loadAsset(
	const char* filePath,
	const AssetMaterialFactory* materialFactory,
	bool loadTextures) noexcept
{
	GLTUT_ASSERT(filePath != nullptr);
	GLTUT_ASSERT(materialFactory != nullptr);

	if (filePath == nullptr || materialFactory == nullptr)
	{
		return nullptr;
	}

	// Load assets/backpack.obj using assimp
	try
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(
			filePath,
			aiProcess_Triangulate |
				aiProcess_FlipUVs |
				aiProcess_GenSmoothNormals |
				aiProcess_CalcTangentSpace);

		GLTUT_CHECK(
			scene != nullptr && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
			"Failed to load model: " + std::string(filePath));

		const std::string modelDirectry = std::filesystem::path(filePath).parent_path().string();

		MaterialsType materials = createMaterials(modelDirectry, *scene, *materialFactory, loadTextures);
		std::vector<Geometry*> geometries;
		MaterialsType geometryMaterials;
		processMeshes(
			*scene,
			materials,
			geometries,
			geometryMaterials);

		return createCompoundGeometryNode(
			scene->mRootNode,
			nullptr,
			geometries,
			geometryMaterials);
	}
	GLTUT_CATCH_ALL("Failed to load an asset from a file");
	return nullptr;
}

AssetLoaderC::MaterialsType AssetLoaderC::createMaterials(
	const std::string& modelDirectory,
	const aiScene& scene,
	const AssetMaterialFactory& materialFactory,
	bool loadTextures)
{
	std::vector<const Material*> result;
	try
	{
		for (u32 matInd = 0; matInd < scene.mNumMaterials; ++matInd)
		{
			aiMaterial* aiMat = scene.mMaterials[matInd];
			Texture2* diffuseTexture = nullptr;
			Texture2* specularTexture = nullptr;
			Texture2* normalTexture = nullptr;

			if (loadTextures)
			{
				diffuseTexture = loadMaterialTexture(modelDirectory, aiMat, aiTextureType_DIFFUSE);
				specularTexture = loadMaterialTexture(modelDirectory, aiMat, aiTextureType_SPECULAR);
				normalTexture = loadMaterialTexture(modelDirectory, aiMat, aiTextureType_HEIGHT);
			}

			const Material* material = materialFactory.createMaterial(
				diffuseTexture,
				specularTexture,
				normalTexture);
			GLTUT_CHECK(material != nullptr, "Failed to create a material");
			result.push_back(material);
		}
	}
	catch (...)
	{
		/// \todo: implement proper cleanup
		/*for (auto* material : result)
		{
			if (material != nullptr)
			{
				mMaterialFactory.removeMaterial(material);
			}
		}*/
		throw;
	}
	return result;
}

Texture2* AssetLoaderC::loadMaterialTexture(
	const std::string& modelDirectory,
	aiMaterial* mat,
	aiTextureType type)
{
	const u32 texturesCount = mat->GetTextureCount(type);
	GLTUT_CHECK(texturesCount <= 1, "Only one texture per type is supported");

	if (texturesCount == 0)
	{
		return nullptr;
	}

	aiString texturePath;
	mat->GetTexture(type, 0, &texturePath);

	// If the path is not absolute, make it relative to the model directory
	if (!std::filesystem::path(texturePath.C_Str()).is_absolute())
	{
		texturePath = (std::filesystem::path(modelDirectory) / std::filesystem::path(texturePath.C_Str())).string().c_str();
	}

	return mEngine.getDevice()->getTextures()->load(texturePath.C_Str());
}

SceneNode* AssetLoaderC::createCompoundGeometryNode(
	aiNode* node,
	SceneNode* parent,
	const std::vector<Geometry*>& geometries,
	const MaterialsType& geometryMaterials)
{
	Matrix4 transform;
	for (u32 r = 0; r < 4; ++r)
	{
		for (u32 c = 0; c < 4; ++c)
		{
			transform(r, c) = node->mTransformation[c][r];
		}
	}

	SceneNode* result = mEngine.getScene()->createGeometryGroup(transform, parent);

	for (u32 meshInd = 0; meshInd < node->mNumMeshes; ++meshInd)
	{
		Geometry* geometry = geometries.at(node->mMeshes[meshInd]);
		GLTUT_CHECK(geometry != nullptr, "Invalid mesh pointer");

		// Obtain the transform
		const Material* material = geometryMaterials.at(node->mMeshes[meshInd]);
		GLTUT_CHECK(material != nullptr, "Invalid material index");
		mEngine.getScene()->createGeometry(geometry, material, Matrix4::identity(), result);
	}

	for (u32 childInd = 0; childInd < node->mNumChildren; ++childInd)
	{
		createCompoundGeometryNode(
			node->mChildren[childInd],
			result,
			geometries,
			geometryMaterials);
	}
	return result;
}

Geometry* AssetLoaderC::createGeometry(aiMesh* mesh)
{
	// data to fill
	std::vector<float> vertices;
	std::vector<u32> indices;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		// normals
		if (mesh->HasNormals())
		{
			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);
		}

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}

		// tangent
		if (mesh->HasTangentsAndBitangents())
		{
			vertices.push_back(mesh->mTangents[i].x);
			vertices.push_back(mesh->mTangents[i].y);
			vertices.push_back(mesh->mTangents[i].z);

			vertices.push_back(mesh->mBitangents[i].x);
			vertices.push_back(mesh->mBitangents[i].y);
			vertices.push_back(mesh->mBitangents[i].z);
		}
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		GLTUT_CHECK(face.mNumIndices == 3, "The model contains non-triangulated faces");
		for (u32 j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	VertexFormat vertexFormat = VERTEX_FORMAT_POS3;
	u32 componentInd = 1;
	if (mesh->HasNormals())
	{
		vertexFormat.setComponentSize(componentInd++, 3);
	}

	if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
	{
		vertexFormat.setComponentSize(componentInd++, 2);
	}

	if (mesh->HasTangentsAndBitangents())
	{
		vertexFormat.setComponentSize(componentInd++, 3);
		vertexFormat.setComponentSize(componentInd++, 3);
	}

	GLTUT_CHECK(vertices.size() % vertexFormat.getTotalSize() == 0, "Invalid vertex size");

	PhongMaterialModel* material = nullptr;

	return mEngine.getDevice()->getGeometries()->create(
		vertexFormat,
		static_cast<u32>(vertices.size() / vertexFormat.getTotalSize()),
		vertices.data(),
		static_cast<u32>(indices.size()),
		indices.data());
}

void AssetLoaderC::processMeshes(
	const aiScene& scene,
	const MaterialsType& materials,
	std::vector<Geometry*>& geometries,
	MaterialsType& geometryMaterials)
{
	GLTUT_CHECK(geometries.empty(), "Geometries vector must be empty");
	GLTUT_CHECK(geometryMaterials.empty(), "Geometry materials vector must be empty");

	try
	{
		geometries.resize(scene.mNumMeshes, nullptr);
		geometryMaterials.resize(scene.mNumMeshes, nullptr);
		for (u32 meshInd = 0; meshInd < scene.mNumMeshes; ++meshInd)
		{
			aiMesh* mesh = scene.mMeshes[meshInd];
			Geometry* geometry = createGeometry(mesh);
			GLTUT_CHECK(geometry != nullptr, "Failed to create geometry");

			geometries[meshInd] = geometry;
			geometryMaterials[meshInd] = materials.at(mesh->mMaterialIndex);
			GLTUT_CHECK(geometryMaterials[meshInd] != nullptr, "Invalid material index");
		}
	}
	catch (...)
	{
		for (auto* geometry : geometries)
		{
			mEngine.getDevice()->getGeometries()->remove(geometry);
		}
		throw;
	}
}

AssetLoader* createAssetLoader(Engine* engine) noexcept
{
	GLTUT_ASSERT(engine != nullptr);
	if (engine == nullptr)
	{
		return nullptr;
	}

	AssetLoader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
	result = new AssetLoaderC(*engine);
	GLTUT_CATCH_ALL_END("Failed to create scene factory");
	return result;
}

void deleteAssetLoader(AssetLoader* factory) noexcept
{
	delete factory;
}

// End of the namespace gltut
}
