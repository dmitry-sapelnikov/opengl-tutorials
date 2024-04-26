#ifndef GLTUT_MOUSE_FPS_CONTROLLER_C_H
#define GLTUT_MOUSE_FPS_CONTROLLER_C_H

//	Includes
#include <array>
#include "engine/core/NonCopyable.h"
#include "engine/scene/camera/CameraController.h"

namespace gltut
{

///	RTS-style camera animator
class FPSCameraControllerC final :
	public CameraController,
	public EventHandler,
	public NonCopyable
{
public:
	/// Constructor
	FPSCameraControllerC(
		Camera& camera,
		float translationSpeed);

	///	Destructor
	~FPSCameraControllerC() noexcept final;

	/// Returns the camera
	Camera& getCamera() noexcept final
	{
		return mCamera;
	}

	/// Updates the camera
	virtual void updateCamera(
		u64 timeMs,
		u32 timeDeltaMs) noexcept final;

	///	Event handler
	virtual void onEvent(const Event& event) noexcept final;

private:
	/// The camera
	Camera& mCamera;

	///	Translation speed
	float mTranslationSpeed;

	bool front = false;
	bool back = false;
	bool left = false;
	bool right = false;
};

//	End of the namespace irr::scene
}

#endif
