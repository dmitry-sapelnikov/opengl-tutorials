#pragma once

// Includes
#include "engine/window/Event.h"

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

