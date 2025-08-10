#pragma once

// Includes
#include "engine/math/Point2.h"
#include "engine/window/Keycodes.h"

namespace gltut
{

// Global classes
/// Contains information about an event
struct Event
{
	/// Enumeration for all event types there are.
	enum class Type
	{
		/// None
		NONE = 0,
		
		/// Mouse event.
		MOUSE,

		/// Keyboard event
		KEYBOARD,

		/// Window resize event
		WINDOW_RESIZE
	};

	/// Platform-specific raw event data
	struct RawEvent
	{
		u64 message = 0;
		void* wParam = nullptr;
		void* lParam = nullptr;
	};

	/// Any kind of mouse event.
	struct MouseEvent
	{
		enum class Type
		{
			/// None
			NONE = 0,

			/// The mouse changed its position.
			MOVE,

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
			WHEEL
		};

		/// Mouse buttons
		struct Buttons
		{
			bool left= false;
			bool right = false;
			bool middle = false;
		};

		/// Event type
		Type type = Type::NONE;

		/// Position of the mouse cursor
		Point2i position{ 0, 0 };

		/// mouse wheel delta, often 1.0 or -1.0, but can have other values < 0.f or > 0.f;
		/** Only valid if event was EMIE_MOUSE_WHEEL */
		float wheel = 0.f;

		/// Button states
		Buttons buttons;
	};

	/// Any kind of keyboard event.
	struct KeyboardEvent
	{
		/// Key which has been pressed or released
		KeyCode key = KeyCode::NONE;

		/// If not true, then the key was left up
		bool pressedDown = false;

		/// True if shift was also pressed
		bool shift = false;

		/// True if ctrl was also pressed
		bool control = false;
	};

	/// Any kind of window resize event
	struct WindowResizeEvent
	{
		Point2u size;
	};

	/// Event type
	Type type = Type::NONE;

	RawEvent raw;

	MouseEvent mouse;

	KeyboardEvent keyboard;

	WindowResizeEvent windowResize;
};

// End of the namespace gltut
}
