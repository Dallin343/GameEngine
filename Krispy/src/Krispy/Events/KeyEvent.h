//
// Created by dallin on 8/12/20.
//

#pragma once

#include "Krispy/Core/Input.h"
#include "Krispy/Events/Event.h"

namespace Krispy {
    class KeyEvent: public Event {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(KeyCode keycode) : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent: public KeyEvent {
    public:
        KeyPressedEvent(KeyCode keycode, bool repeat) : KeyEvent(keycode), m_Repeat(repeat) {}

        inline int IsRepeat() const { return m_Repeat; }

        std::string ToString() const override {
            std::stringstream ss;
            const char * repeat = m_Repeat ? "true" : "false";
            ss << "KeyPressedEvent: " << m_KeyCode << " (Repeat: " << repeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_Repeat;
    };

    class KeyReleasedEvent: public KeyEvent {
    public:
        KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent: public KeyEvent {
    public:
        KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}


