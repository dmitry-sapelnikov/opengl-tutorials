#pragma once

// Includes
#include "imgui/imgui.h"

namespace gltut
{

// Global classes

// Forward declarations
class Engine;

/// Interface for the ImGui engine integration
class EngineImgui
{
public:
	/// Virtual destructor
	virtual ~EngineImgui() noexcept = default;

	/// Renders the ImGui draw data
	virtual void newFrame() noexcept = 0;
};

// Global functions
/**
	Creates an instance of the EngineImgui
	\note If you create the instance, you must call imgui->newFrame();
	every frame inside the engine loop
*/
EngineImgui* createEngineImgui(gltut::Engine* engine) noexcept;

/// Deletes the EngineImgui instance
void deleteEngineImgui(EngineImgui* engineImgui) noexcept;

}
