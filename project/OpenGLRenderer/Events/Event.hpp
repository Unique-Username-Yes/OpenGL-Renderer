#pragma once

namespace OpenGLRenderer
{
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyDown, KeyUp, KeyTyped
    };

    class Event
    {
        public:
            virtual EventType GetEventType() const = 0;
    };
}
