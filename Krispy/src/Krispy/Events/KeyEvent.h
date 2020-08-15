//
// Created by dallin on 8/12/20.
//

#pragma once

#include "Event.h"

namespace Krispy {
    class KeyEvent: public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    class KeyPressedEvent: public KeyEvent {
    public:
        KeyPressedEvent(int keycode, bool repeat) : KeyEvent(keycode), m_Repeat(repeat) {}

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
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}


