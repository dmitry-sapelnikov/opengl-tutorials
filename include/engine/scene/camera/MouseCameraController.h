#ifndef GLTUT_MOUSE_CAMERA_CONTROLLER_H
#define GLTUT_MOUSE_CAMERA_CONTROLLER_H

//	Includes
#include "engine/scene/camera/CameraController.h"

namespace gltut
{
// Global functions
/// Creates a mouse camera controller
CameraController* createMouseCameraController(
	Camera& camera,
	float rotationSpeed = 100.0f,
	float zoomSpeed = 100.0f,
	float translationSpeed = 100.0f,
	float targetMinDistance = 1.0f,
	float targetMaxDistance = 100.0f) noexcept;

//	End of the namespace irr::scene
}

#endif
