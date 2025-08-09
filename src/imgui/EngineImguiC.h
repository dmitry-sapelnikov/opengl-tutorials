#pragma once
#include "imgui/EngineImgui.h"
#include "engine/core/NonCopyable.h"
#include "engine/Engine.h"

namespace gltut
{
class EngineImguiC final : public EngineImgui, public NonCopyable
{
public:
	/// Constructor
	EngineImguiC(Engine& engine);

	/// Virtual destructor
	virtual ~EngineImguiC() noexcept final;

	/// Creates a new Imgui frame
	void newFrame() noexcept final;

private:
	Engine& mEngine;

	std::unique_ptr<RenderObject> mRenderObject;

	std::unique_ptr<EventHandler> mEventHandler;

	/// Render pass for Imgui
	RenderPass* mRenderPass = nullptr;
};

// End of namespace gltut
}
