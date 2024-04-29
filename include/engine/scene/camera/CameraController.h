#ifndef OPENGL_TUTORIALS_CAMERA_CONTROLLER_H
#define OPENGL_TUTORIALS_CAMERA_CONTROLLER_H

// Includes
#include "engine/scene/camera/Camera.h"

namespace gltut
{
// Global classes
/// The class represents a camera controller interface
class CameraController
{
public:
	/// Virtual destructor
	virtual ~CameraController() noexcept = default;

	/// Returns the camera
	virtual Camera& getCamera() noexcept = 0;

	/// Updates the camera
	virtual void updateCamera(
		u64 timeMs,
		u32 timeDeltaMs) noexcept = 0;
};

// Global functions
/// Creates a FPS camera controller
CameraController* createFPSCameraController(
	Camera& camera,
	float translationSpeed,
	float mouseSensitivity) noexcept;

/// Creates a mouse camera controller
CameraController* createMouseCameraController(
	Camera& camera,
	float rotationSpeed = 0.1f,
	float zoomSpeed = 100.0f,
	float targetMinDistance = 1.0f,
	float targetMaxDistance = 100.0f) noexcept;

// End of the namespace gltut
}

#endif
