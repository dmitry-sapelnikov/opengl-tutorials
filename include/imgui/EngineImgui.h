#pragma once
#include "imgui/imgui.h"

namespace gltut
{

// Global classes
class Engine;

/// Interface for the ImGui engine integration
class EngineImgui
{
public:
	virtual ~EngineImgui() noexcept = default;

	virtual void newFrame() noexcept = 0;
};

// Global functions
/// Creates an instance of the EngineImgui
EngineImgui* createEngineImgui(gltut::Engine* engine) noexcept;

/// Deletes the EngineImgui instance
void deleteEngineImgui(EngineImgui* engineImgui) noexcept;

}
