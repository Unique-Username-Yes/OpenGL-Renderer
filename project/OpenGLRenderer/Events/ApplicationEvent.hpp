#pragma once

#include "Event.hpp"

namespace OpenGLRenderer
{
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		~WindowCloseEvent() {}

		virtual EventType GetEventType() const override { return EventType::WindowClose; }
	};
}