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
	virtual void updateCamera() noexcept = 0;
};

// End of the namespace gltut
}

#endif
