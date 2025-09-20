// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#include "engine/Engine.h"
#include "imgui/EngineImgui.h"

int main(int, char**)
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;

	GLTUT_CATCH_ALL_BEGIN
		engine.reset(gltut::createEngine(1280, 720));
		GLTUT_CHECK(engine != nullptr, "Failed to create Engine instance");
		engine->getWindow()->setTitle("Dear ImGui OpenGL Example");
		engine->getWindow()->showFPS(true);

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui instance");

		do
		{
			imgui->newFrame();
			ImGui::ShowDemoWindow();
		} while (engine->update());
	GLTUT_CATCH_ALL_END("Failed to run 10_imgui example");

	gltut::deleteEngineImgui(imgui);
	return 0;
}
