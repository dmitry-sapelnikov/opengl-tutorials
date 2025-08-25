// Includes
#include "SceneFactoryC.h"
#include <filesystem>
#include "engine/core/Check.h"

namespace gltut
{

// Global classes
SceneFactoryC::SceneFactoryC(
	GraphicsDevice& device,
	Scene& scene,
	MaterialFactory& materialFactory) :

	mDevice(device),
	mScene(scene),
	mMaterialFactory(materialFactory)
{
}

SceneNode* SceneFactoryC::loadModel(
	const char* filePath,
	PhongShaderModel* phongShader) noexcept
{
	GLTUT_ASSERT(filePath != nullptr);
	GLTUT_ASSERT(phongShader != nullptr);
	if (filePath == nullptr || phongShader == nullptr)
	{
		return nullptr;
	}

	// Load assets/backpack.obj using assimp
	GLTUT_CATCH_ALL_BEGIN
		Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		filePath,
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs);

		GLTUT_CHECK(
			scene != nullptr && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
			"Failed to load model: " + std::string(filePath));

		const std::string modelDirectry = std::filesystem::path(filePath).parent_path().string();

		auto materials = createMaterials(modelDirectry, *scene, *phongShader);
		std::vector<Geometry*> geometries;
		std::vector<PhongMaterialModel*> geometryMaterials;
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

	GLTUT_CATCH_ALL_END("Failed to load a geometry node from a file");

	return nullptr;
}

std::vector<PhongMaterialModel*> SceneFactoryC::createMaterials(
	const std::string& modelDirectory,
	const aiScene& scene,
	const PhongShaderModel& phongShader)
{
	std::vector<PhongMaterialModel*> result;
	try
	{
		for (u32 matInd = 0; matInd < scene.mNumMaterials; ++matInd)
		{
			aiMaterial* aiMat = scene.mMaterials[matInd];
			PhongMaterialModel* material = mMaterialFactory.createPhongMaterial(&phongShader, true);
			GLTUT_CHECK(material != nullptr, "Failed to create a Phong material model");

			material->setDiffuse(loadMaterialTexture(modelDirectory, aiMat, aiTextureType_DIFFUSE));
			material->setSpecular(loadMaterialTexture(modelDirectory, aiMat, aiTextureType_SPECULAR));

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

Texture* SceneFactoryC::loadMaterialTexture(
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

	return mDevice.getTextures()->load(texturePath.C_Str());
}

SceneNode* SceneFactoryC::createCompoundGeometryNode(
	aiNode* node,
	SceneNode* parent,
	const std::vector<Geometry*>& geometries,
	const std::vector<PhongMaterialModel*>& geometryMaterials)
{
	Matrix4 transform;
	for (u32 r = 0; r < 4; ++r)
	{
		for (u32 c = 0; c < 4; ++c)
		{
			transform(r, c) = node->mTransformation[c][r];
		}
	}

	SceneNode* result = mScene.createGroup(transform, parent);

	for (u32 meshInd = 0; meshInd < node->mNumMeshes; ++meshInd)
	{
		Geometry* geometry = geometries.at(node->mMeshes[meshInd]);
		GLTUT_CHECK(geometry != nullptr, "Invalid mesh pointer");

		// Obtain the transform
		const PhongMaterialModel* material = geometryMaterials.at(node->mMeshes[meshInd]);
		GLTUT_CHECK(material != nullptr, "Invalid material index");
		mScene.createGeometry(geometry, material->getMaterial(), Matrix4::identity(), result);
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

Geometry* SceneFactoryC::createGeometry(aiMesh* mesh)
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

	GLTUT_CHECK(vertices.size() % vertexFormat.getTotalSize() == 0, "Invalid vertex size");

	PhongMaterialModel* material = nullptr;

	return mDevice.getGeometries()->create(
		vertexFormat,
		static_cast<u32>(vertices.size() / vertexFormat.getTotalSize()),
		vertices.data(),
		static_cast<u32>(indices.size()),
		indices.data());
}

void SceneFactoryC::processMeshes(
	const aiScene& scene,
	const std::vector<PhongMaterialModel*>& materials,
	std::vector<Geometry*>& geometries,
	std::vector<PhongMaterialModel*>& geometryMaterials)
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
			if (geometry != nullptr)
			{
				mDevice.getGeometries()->remove(geometry);
			}
		}
		throw;
	}
}

SceneFactory* createSceneFactory(
	GraphicsDevice& device,
	Scene& scene,
	MaterialFactory& materialFactory) noexcept
{
	SceneFactory* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = new SceneFactoryC(device, scene, materialFactory);
	GLTUT_CATCH_ALL_END("Failed to create scene factory");
	return result;
}

void deleteSceneFactory(SceneFactory* factory) noexcept
{
	delete factory;
}

// End of the namespace gltut
}
