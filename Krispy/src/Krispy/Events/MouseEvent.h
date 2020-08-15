//
// Created by dallin on 8/12/20.
//

#pragma once

#include "Event.h"

namespace Krispy {
    class MouseMovedEvent: public Event {
    public:
        MouseMovedEvent(float x, float y): m_PosX(x), m_PosY(y) {}

        inline float GetX() const { return m_PosX; }
        inline float GetY() const { return m_PosY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_PosX << ", " << m_PosY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_PosX, m_PosY;
    };

    class MouseScrolledEvent: public Event {
    public:
        MouseScrolledEvent(float offsetX, float offsetY): m_OffsetX(offsetX), m_OffsetY(offsetY) {}

        inline float GetXOffset() const { return m_OffsetX; }
        inline float GetYOffset() const { return m_OffsetY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_OffsetX, m_OffsetY;
    };

    class MouseButtonEvent: public Event {
    public:
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

    protected:
        MouseButtonEvent(int button) : m_Button(button) {};
        int m_Button;
    };

    class MouseButtonPressedEvent: public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button): MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent: public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button): MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}


