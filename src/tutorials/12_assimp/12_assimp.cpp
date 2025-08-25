#include "engine/Engine.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main(int, char**)
{
	

	std::unique_ptr<gltut::Engine> engine;
	GLTUT_CATCH_ALL_BEGIN
		// Load assets/backpack.obj using assimp
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(
			"assets/backpack.obj",
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace);

		GLTUT_CHECK(
			scene != nullptr && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
			"Failed to load model: " + std::string(importer.GetErrorString()));

		engine.reset(gltut::createEngine(1280, 720));
		GLTUT_CHECK(engine != nullptr, "Failed to create Engine instance");
		engine->getWindow()->setTitle("Assimp OpenGL Example");
		engine->getWindow()->showFPS(true);
		do
		{
		} while (engine->update());
	GLTUT_CATCH_ALL_END("Failed to run 10_imgui example");
	return 0;
}
