#include "Event.hpp"
#include <string>
#include <sstream>

namespace OpenGLRenderer 
{
    class KeyEvent : public Event 
    {
        public:
            inline int GetKeyCode() const { return m_KeyCode; }

            std::string ToString() const {
                std::stringstream ss;
                ss << "Key event for: " << m_KeyCode;
                return ss.str();
            }

        protected:
            KeyEvent(int keyCode): m_KeyCode(keyCode) {}
        private:
            int m_KeyCode;
    };

    class KeyDownEvent : public KeyEvent 
    {
        public:
            KeyDownEvent(int keyCode, int repeatCount): KeyEvent(keyCode) {}
            ~KeyDownEvent() {}

            virtual EventType GetEventType() const override { return EventType::KeyDown; }
    };

    class KeyUpEvent : public KeyEvent 
    {
        public:
            KeyUpEvent(int keyCode): KeyEvent(keyCode) {}
            ~KeyUpEvent() {}
            virtual EventType GetEventType() const override { return EventType::KeyUp; }
    };

    class KeyTypedEvent : public KeyEvent 
    {
        public:
            KeyTypedEvent(int keyCode): KeyEvent(keyCode) {}
            ~KeyTypedEvent() {}
            virtual EventType GetEventType() const override { return EventType::KeyTyped; }
    };
}