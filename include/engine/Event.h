#ifndef OPENGL_TUTORIALS_EVENT_H
#define OPENGL_TUTORIALS_EVENT_H

// Includes
#include "engine/Core/Types.h"
#include "engine/Keycodes.h"

namespace gltut
{

// Global classes
/// Contains information about an event
struct Event
{
	/// Enumeration for all event types there are.
	enum class Type
	{
		/// Mouse event.
		MOUSE,

		/// Keyboard event
		KEYBOARD,

		/// Window resize event
		WINDOW_RESIZE
	};

	/// Any kind of mouse event.
	struct MouseEvent
	{
		enum class Type
		{
			/// Left mouse button was pressed down.
			LEFT_BUTTON_DOWN,

			/// Right mouse button was pressed down.
			RIGHT_BUTTON_DOWN,

			/// Middle mouse button was pressed down
			MIDDLE_BUTTON_DOWN,

			/// Left mouse button was released
			LEFT_BUTTON_UP,

			/// Right mouse button was released
			RIGHT_BUTTON_UP,

			/// Middle mouse button was released
			MIDDLE_BUTTON_UP,

			/// The mouse wheel was scrolled
			WHEEL,

			/// The mouse changed its position.
			MOVE
		};

		/// Mouse buttons
		enum class Button : u32
		{
			LEFT = 0,
			RIGHT,
			MIDDLE
		};

		/// Event type
		Type type;

		/// x-position of the mouse cursor
		int32 x;

		/// y-position of the mouse cursor
		int32 y;

		/// mouse wheel delta, often 1.0 or -1.0, but can have other values < 0.f or > 0.f;
		/** Only valid if event was EMIE_MOUSE_WHEEL */
		float wheel;

		/// A bit map of button states
		u32 buttonStates;

		/// Returns if a button is pressed
		bool isPressed(Button button) const
		{ 
			return buttonStates & (1 << static_cast<u32>(button));
		}
	};

	/// Any kind of keyboard event.
	struct KeyboardEvent
	{
		/// Key which has been pressed or released
		KeyCode key;

		/// If not true, then the key was left up
		bool pressedDown;

		/// True if shift was also pressed
		bool shift;

		/// True if ctrl was also pressed
		bool control;
	};

	/// Any kind of window resize event
	struct WindowResizeEvent
	{
		/// New width of the window
		u32 width;

		/// New height of the window
		u32 height;
	};

	/// Event type
	Type type;

	/// Union of all possible events
	union
	{
		struct MouseEvent mouse;
		struct KeyboardEvent keyboard;
		struct WindowResizeEvent windowResize;
	};
};

// End of the namespace gltut
}

#endif
