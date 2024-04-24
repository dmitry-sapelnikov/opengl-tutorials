#ifndef OPENGL_TUTORIALS_EVENT_HANDLER_H
#define OPENGL_TUTORIALS_EVENT_HANDLER_H

// Includes
#include "engine/Event.h"

namespace gltut
{

/// Interface to handle events
class EventHandler
{
public:
	/// Virtual destructor
	virtual ~EventHandler() noexcept = default;

	/// Called when an event occurs
	virtual void onEvent(const Event& event) noexcept = 0;
};

// End of the namespace gltut
}

#endif
