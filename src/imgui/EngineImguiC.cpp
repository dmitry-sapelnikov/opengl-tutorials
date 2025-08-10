#include "EngineImguiC.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "engine/Engine.h"
#include "./imgui/imgui_impl_win32.h"
#include "./imgui/imgui_impl_opengl3.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

namespace gltut
{

// Local classes
namespace
{

// Imgui render object
// TODO: this is a temporary solution,
// ImGui_ImplOpenGL3_RenderDrawData should be replaced with engin graphics backend
class ImguiRenderObject : public RenderObject
{
public:
	void render(u32 materialPass) const noexcept final
	{
		GLTUT_CATCH_ALL_BEGIN
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GLTUT_CATCH_ALL_END("Failed to render ImGui frame")
	}
};

// Imgui event handler
// TODO: this is a temporary solution,
// ImGui_ImplWin32_WndProcHandler should be replaced with handling
// of engine-specific events
class ImguiEventHandler : public EventHandler
{
public:
	ImguiEventHandler(HWND hwnd) noexcept :
		mHwnd(hwnd)
	{
	}

	bool onEvent(const Event& event) noexcept
	{
		ImGui_ImplWin32_WndProcHandler(
			mHwnd,
			(UINT)event.raw.message,
			(WPARAM)event.raw.wParam,
			(LPARAM)event.raw.lParam);

		/// Stop event propagation when the user interacts with GUI
		return ImGui::IsAnyItemActive();
	}

private:
	/// The window handle
	HWND mHwnd;
};

// End of the local namespace
}

// Global classes
EngineImguiC::EngineImguiC(Engine& engine) :
	mEngine(engine)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	
	auto* context = ImGui::CreateContext();
	GLTUT_CHECK(context != nullptr, "Failed to create ImGui context");

	ImGuiIO& io = ImGui::GetIO();
	// Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Disable ini file saving
	io.IniFilename = nullptr;

	// Disable log file saving
	io.LogFilename = nullptr;

	/// \todo: this is a temporary solution,
	/// ImGui_ImplWin32_InitForOpenGL and ImGui_ImplOpenGL3_Init
	/// should be replaced with engine-specific graphics backend
	
	const bool win32InitResult = ImGui_ImplWin32_InitForOpenGL(
		engine.getWindow()->getHandle());
	GLTUT_CHECK(win32InitResult, "Failed to initialize ImGui for OpenGL");

	const bool openglInitResult = ImGui_ImplOpenGL3_Init();
	GLTUT_CHECK(openglInitResult, "Failed to initialize ImGui for OpenGL");

	mRenderObject = std::make_unique<ImguiRenderObject>();
	GLTUT_CHECK(mRenderObject != nullptr, "Failed to create ImguiRenderObject");

	mRenderPass = engine.getRenderPipeline()->createPass(
		nullptr,
		mRenderObject.get(),
		engine.getDevice()->getWindowFramebuffer(),
		0,
		nullptr,
		false,
		nullptr);

	mEventHandler = std::make_unique<ImguiEventHandler>(
		static_cast<HWND>(engine.getWindow()->getHandle()));

	GLTUT_CHECK(mEventHandler != nullptr, "Failed to create ImguiEventHandler");
	engine.getWindow()->addEventHandler(mEventHandler.get());
}

EngineImguiC::~EngineImguiC() noexcept
{
	if (mRenderPass != nullptr)
	{
		mEngine.getRenderPipeline()->removePass(mRenderPass);
	}

	if (mEventHandler != nullptr)
	{
		mEngine.getWindow()->removeEventHandler(mEventHandler.get());
	}

	GLTUT_CATCH_ALL_BEGIN
		/// \todo: this is a temporary solution,
		/// ImGui_ImplOpenGL3_Shutdown and ImGui_ImplWin32_Shutdown
		/// should be replaced with engine-specific graphics backend
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	GLTUT_CATCH_ALL_END("Failed to destroy ImGui context")
}

void EngineImguiC::newFrame() noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	GLTUT_CATCH_ALL_END("Failed to create new ImGui frame")
}

// Global functions
EngineImgui* createEngineImgui(Engine* engine) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		return new EngineImguiC(*engine);
	GLTUT_CATCH_ALL_END("Failed to create EngineImguiC instance")
		return nullptr;
}

void deleteEngineImgui(EngineImgui* engineImgui) noexcept
{
	delete engineImgui;
}

// End of the namespace gltut
}
