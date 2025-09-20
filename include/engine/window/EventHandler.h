// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

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

	/**
		\brief Called when an event occurs
		\return True if the event was handled, false to continue processing
	*/
	virtual bool onEvent(const Event& event) noexcept = 0;
};

// End of the namespace gltut
}
